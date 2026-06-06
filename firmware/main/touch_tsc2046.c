#include "touch_tsc2046.h"

#include <string.h>
#include "board_pins.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_log.h"
#include "shared_spi.h"
#include "ui.h"

#define TSC2046_CMD_X 0xD0
#define TSC2046_CMD_Y 0x90
#define TSC2046_CMD_Z 0x30
#define TSC2046_CMD_DEFAULT 0x84
#define TSC2046_PRESS_THRESHOLD 50

static const char *TAG = "touch_tsc2046";

static spi_device_handle_t s_touch_spi;
static touch_sample_t s_last_sample;

typedef struct {
    uint16_t tl_x;
    uint16_t tl_y;
    uint16_t br_x;
    uint16_t br_y;
    uint16_t width;
    uint16_t height;
} touch_calibration_t;

static const touch_calibration_t s_cal = {
    .tl_x = 2320,
    .tl_y = 3850,
    .br_x = 4045,
    .br_y = 2205,
    .width = 480,
    .height = 320,
};

static uint16_t clamp_u16(int32_t value, uint16_t max_value)
{
    if (value < 0) {
        return 0;
    }
    if (value > max_value) {
        return max_value;
    }
    return (uint16_t)value;
}

static uint16_t map_axis(uint16_t raw, uint16_t raw_min, uint16_t raw_max, uint16_t out_max)
{
    const int32_t delta_raw = (int32_t)raw_max - (int32_t)raw_min;
    if (delta_raw == 0) {
        return 0;
    }

    const int32_t mapped = ((int32_t)raw - (int32_t)raw_min) * (int32_t)out_max / delta_raw;
    return clamp_u16(mapped, out_max);
}

static esp_err_t send_command(uint8_t command, uint16_t *value)
{
    uint8_t tx_buf[3] = {command, 0x00, 0x00};
    uint8_t rx_buf[3] = {0};
    spi_transaction_t transaction = {
        .length = sizeof(tx_buf) * 8,
        .tx_buffer = tx_buf,
        .rx_buffer = rx_buf,
    };

    ESP_RETURN_ON_ERROR(spi_device_polling_transmit(s_touch_spi, &transaction), TAG, "touch SPI transaction failed");
    *value = ((uint16_t)rx_buf[1] << 4) | ((uint16_t)rx_buf[2] >> 4);
    return ESP_OK;
}

esp_err_t touch_tsc2046_init(void)
{
    ESP_LOGI(TAG, "initializing TSC2046/XPT2046 touch SPI");

    ESP_RETURN_ON_ERROR(shared_spi_init(), TAG, "failed to initialize shared SPI bus");

    const spi_device_interface_config_t dev_config = {
        .clock_speed_hz = BOARD_TOUCH_CLOCK_HZ,
        .mode = 0,
        .spics_io_num = BOARD_TOUCH_CS,
        .queue_size = 1,
        .command_bits = 0,
        .address_bits = 0,
    };
    ESP_RETURN_ON_ERROR(spi_bus_add_device(BOARD_SHARED_SPI_HOST, &dev_config, &s_touch_spi), TAG,
                        "failed to add touch SPI device");

    return ESP_OK;
}

bool touch_tsc2046_read(touch_sample_t *sample)
{
    uint16_t raw_x = 0;
    uint16_t raw_y = 0;
    uint16_t raw_z = 0;

    if (send_command(TSC2046_CMD_Z | TSC2046_CMD_DEFAULT, &raw_z) != ESP_OK) {
        return false;
    }

    memset(sample, 0, sizeof(*sample));
    sample->raw_z = raw_z;

    if (raw_z <= TSC2046_PRESS_THRESHOLD) {
        sample->pressed = false;
        s_last_sample = *sample;
        return true;
    }

    if (send_command(TSC2046_CMD_X | TSC2046_CMD_DEFAULT, &raw_x) != ESP_OK ||
        send_command(TSC2046_CMD_Y | TSC2046_CMD_DEFAULT, &raw_y) != ESP_OK) {
        return false;
    }

    sample->pressed = true;
    sample->raw_x = raw_x;
    sample->raw_y = raw_y;
    sample->x = map_axis(raw_x, s_cal.tl_x, s_cal.br_x, s_cal.width - 1);
    sample->y = map_axis(raw_y, s_cal.tl_y, s_cal.br_y, s_cal.height - 1);
    s_last_sample = *sample;
    return true;
}

void touch_tsc2046_register_lvgl(lv_indev_t *indev)
{
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touch_tsc2046_lvgl_read);
}

void touch_tsc2046_lvgl_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    (void)indev;
    touch_sample_t sample;

    if (!touch_tsc2046_read(&sample)) {
        sample = s_last_sample;
    }

    data->state = sample.pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    data->point.x = sample.x;
    data->point.y = sample.y;
    ui_set_touch_sample(sample.raw_x, sample.raw_y, sample.raw_z, sample.pressed);
}
