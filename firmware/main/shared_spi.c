#include "shared_spi.h"

#include <stdbool.h>
#include "board_pins.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_log.h"

static const char *TAG = "shared_spi";

static bool s_initialized;

esp_err_t shared_spi_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    const spi_bus_config_t bus_config = {
        .mosi_io_num = BOARD_TOUCH_MOSI,
        .miso_io_num = BOARD_TOUCH_MISO,
        .sclk_io_num = BOARD_TOUCH_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    esp_err_t err = spi_bus_initialize(BOARD_SHARED_SPI_HOST, &bus_config, SPI_DMA_CH_AUTO);
    if (err == ESP_ERR_INVALID_STATE) {
        ESP_LOGW(TAG, "shared SPI bus was already initialized");
        s_initialized = true;
        return ESP_OK;
    }

    ESP_RETURN_ON_ERROR(err, TAG, "failed to initialize shared SPI bus");
    s_initialized = true;
    return ESP_OK;
}
