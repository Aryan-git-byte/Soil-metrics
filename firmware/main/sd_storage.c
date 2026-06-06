#include "sd_storage.h"

#include <stdio.h>
#include "board_pins.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "shared_spi.h"

static const char *TAG = "sd_storage";
static bool s_mounted;

esp_err_t sd_storage_init(void)
{
    ESP_RETURN_ON_ERROR(shared_spi_init(), TAG, "shared SPI init failed");

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 3,
        .allocation_unit_size = 16 * 1024,
    };

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = BOARD_SHARED_SPI_HOST;

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = BOARD_SD_CS;
    slot_config.host_id = BOARD_SHARED_SPI_HOST;

    sdmmc_card_t *card = NULL;
    esp_err_t err = esp_vfs_fat_sdspi_mount(BOARD_SD_MOUNT_POINT, &host, &slot_config, &mount_config, &card);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "SD card mount failed: %s", esp_err_to_name(err));
        s_mounted = false;
        return err;
    }

    sdmmc_card_print_info(stdout, card);
    s_mounted = true;
    return ESP_OK;
}

esp_err_t sd_storage_append_reading(const soil_reading_t *reading)
{
    if (!s_mounted || reading == NULL || !reading->valid) {
        return ESP_ERR_INVALID_STATE;
    }

    char path[64];
    snprintf(path, sizeof(path), "%s/readings.csv", BOARD_SD_MOUNT_POINT);

    FILE *file = fopen(path, "a");
    if (file == NULL) {
        return ESP_FAIL;
    }

    fprintf(file, "%lld,%.1f,%.1f,%u,%.1f,%u,%u,%u\n",
            (long long)reading->updated_us,
            reading->moisture_percent,
            reading->temperature_c,
            reading->ec_us_cm,
            reading->ph,
            reading->nitrogen_mg_kg,
            reading->phosphorus_mg_kg,
            reading->potassium_mg_kg);
    fclose(file);
    return ESP_OK;
}
