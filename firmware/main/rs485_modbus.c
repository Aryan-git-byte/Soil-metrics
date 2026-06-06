#include "rs485_modbus.h"

#include <stdbool.h>
#include <string.h>
#include "board_pins.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MODBUS_FUNC_READ_HOLDING 0x03
#define MODBUS_MAX_REGISTERS 32

static const char *TAG = "rs485_modbus";

static uint16_t modbus_crc16(const uint8_t *data, size_t len)
{
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < len; ++i) {
        crc ^= data[i];
        for (int bit = 0; bit < 8; ++bit) {
            if ((crc & 0x0001) != 0) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

static void rs485_set_transmit(bool transmit)
{
    gpio_set_level(BOARD_RS485_DE_RE, transmit ? 1 : 0);
}

esp_err_t rs485_modbus_init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = BOARD_RS485_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_RETURN_ON_ERROR(uart_driver_install(BOARD_RS485_UART, 512, 512, 0, NULL, 0), TAG,
                        "failed to install RS485 UART driver");
    ESP_RETURN_ON_ERROR(uart_param_config(BOARD_RS485_UART, &uart_config), TAG, "failed to configure RS485 UART");
    ESP_RETURN_ON_ERROR(uart_set_pin(BOARD_RS485_UART, BOARD_RS485_TX, BOARD_RS485_RX,
                                     UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE),
                        TAG, "failed to set RS485 UART pins");

    const gpio_config_t dir_config = {
        .pin_bit_mask = 1ULL << BOARD_RS485_DE_RE,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&dir_config), TAG, "failed to configure RS485 direction pin");
    rs485_set_transmit(false);

    return ESP_OK;
}

esp_err_t rs485_modbus_read_holding_registers(uint8_t slave_addr,
                                              uint16_t start_reg,
                                              uint16_t *registers,
                                              size_t register_count,
                                              uint32_t timeout_ms)
{
    if (registers == NULL || register_count == 0 || register_count > MODBUS_MAX_REGISTERS) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t request[8] = {
        slave_addr,
        MODBUS_FUNC_READ_HOLDING,
        (uint8_t)(start_reg >> 8),
        (uint8_t)(start_reg & 0xFF),
        (uint8_t)(register_count >> 8),
        (uint8_t)(register_count & 0xFF),
        0,
        0,
    };
    const uint16_t request_crc = modbus_crc16(request, 6);
    request[6] = (uint8_t)(request_crc & 0xFF);
    request[7] = (uint8_t)(request_crc >> 8);

    uart_flush_input(BOARD_RS485_UART);
    rs485_set_transmit(true);
    vTaskDelay(pdMS_TO_TICKS(2));
    const int written = uart_write_bytes(BOARD_RS485_UART, request, sizeof(request));
    if (written != sizeof(request)) {
        rs485_set_transmit(false);
        ESP_LOGE(TAG, "failed to write full Modbus request");
        return ESP_FAIL;
    }

    esp_err_t err = uart_wait_tx_done(BOARD_RS485_UART, pdMS_TO_TICKS(timeout_ms));
    rs485_set_transmit(false);
    ESP_RETURN_ON_ERROR(err, TAG, "Modbus request TX timeout");

    const size_t expected_len = 5 + register_count * 2;
    uint8_t response[5 + MODBUS_MAX_REGISTERS * 2] = {0};
    const int read_len = uart_read_bytes(BOARD_RS485_UART, response, expected_len, pdMS_TO_TICKS(timeout_ms));
    ESP_RETURN_ON_FALSE(read_len == expected_len, ESP_ERR_TIMEOUT, TAG, "Modbus response timeout");

    const uint16_t actual_crc = ((uint16_t)response[expected_len - 1] << 8) | response[expected_len - 2];
    const uint16_t expected_crc = modbus_crc16(response, expected_len - 2);
    ESP_RETURN_ON_FALSE(actual_crc == expected_crc, ESP_ERR_INVALID_CRC, TAG, "Modbus CRC mismatch");
    ESP_RETURN_ON_FALSE(response[0] == slave_addr, ESP_ERR_INVALID_RESPONSE, TAG, "Modbus slave mismatch");
    ESP_RETURN_ON_FALSE(response[1] == MODBUS_FUNC_READ_HOLDING, ESP_ERR_INVALID_RESPONSE, TAG,
                        "Modbus function mismatch");
    ESP_RETURN_ON_FALSE(response[2] == register_count * 2, ESP_ERR_INVALID_RESPONSE, TAG,
                        "Modbus byte count mismatch");

    for (size_t i = 0; i < register_count; ++i) {
        registers[i] = ((uint16_t)response[3 + i * 2] << 8) | response[4 + i * 2];
    }

    return ESP_OK;
}
