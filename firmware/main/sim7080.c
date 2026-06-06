#include "sim7080.h"

#include <string.h>
#include "board_pins.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "sim7080";

static esp_err_t sim7080_send_command(const char *command, char *response, size_t response_len, uint32_t timeout_ms)
{
    uart_flush_input(BOARD_SIM_UART);
    uart_write_bytes(BOARD_SIM_UART, command, strlen(command));
    uart_write_bytes(BOARD_SIM_UART, "\r\n", 2);

    int len = uart_read_bytes(BOARD_SIM_UART, response, response_len - 1, pdMS_TO_TICKS(timeout_ms));
    if (len <= 0) {
        response[0] = '\0';
        return ESP_ERR_TIMEOUT;
    }

    response[len] = '\0';
    return ESP_OK;
}

esp_err_t sim7080_init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = BOARD_SIM_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_RETURN_ON_ERROR(uart_driver_install(BOARD_SIM_UART, 2048, 2048, 0, NULL, 0), TAG,
                        "failed to install SIM UART driver");
    ESP_RETURN_ON_ERROR(uart_param_config(BOARD_SIM_UART, &uart_config), TAG, "failed to configure SIM UART");
    ESP_RETURN_ON_ERROR(uart_set_pin(BOARD_SIM_UART, BOARD_SIM_TX, BOARD_SIM_RX,
                                     UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE),
                        TAG, "failed to set SIM UART pins");

    const gpio_config_t pwrkey_config = {
        .pin_bit_mask = 1ULL << BOARD_SIM_PWRKEY,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&pwrkey_config), TAG, "failed to configure SIM PWRKEY");
    gpio_set_level(BOARD_SIM_PWRKEY, BOARD_SIM_PWRKEY_INACTIVE_LEVEL);

    return ESP_OK;
}

esp_err_t sim7080_power_key_pulse(void)
{
    gpio_set_level(BOARD_SIM_PWRKEY, BOARD_SIM_PWRKEY_ACTIVE_LEVEL);
    vTaskDelay(pdMS_TO_TICKS(1200));
    gpio_set_level(BOARD_SIM_PWRKEY, BOARD_SIM_PWRKEY_INACTIVE_LEVEL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    return ESP_OK;
}

esp_err_t sim7080_check_ready(bool *ready)
{
    char response[128];
    esp_err_t err = sim7080_send_command("AT", response, sizeof(response), 1000);
    if (err != ESP_OK || strstr(response, "OK") == NULL) {
        vTaskDelay(pdMS_TO_TICKS(200));
        err = sim7080_send_command("AT", response, sizeof(response), 1000);
    }

    *ready = (err == ESP_OK && strstr(response, "OK") != NULL);
    return err;
}
