#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "app_state.h"
#include "board_pins.h"
#include "display_i80.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "sd_storage.h"
#include "sim7080.h"
#include "soil_sensor.h"
#include "touch_tsc2046.h"
#include "ui.h"

static const char *TAG = "app_main";

static void lvgl_tick_cb(void *arg)
{
    (void)arg;
    lv_tick_inc(1);
}

static void lvgl_task(void *arg)
{
    (void)arg;
    while (true) {
        uint32_t delay_ms = lv_timer_handler();
        if (delay_ms < 5) {
            delay_ms = 5;
        }
        if (delay_ms > 50) {
            delay_ms = 50;
        }
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

static void soil_sensor_task(void *arg)
{
    (void)arg;

    while (true) {
        soil_reading_t reading = {0};
        esp_err_t err = soil_sensor_read(&reading);
        app_state_set_soil_reading(&reading);

        if (err == ESP_OK) {
            ESP_LOGI(TAG, "soil: moisture=%.1f temp=%.1f ec=%u ph=%.1f n=%u p=%u k=%u",
                     reading.moisture_percent,
                     reading.temperature_c,
                     reading.ec_us_cm,
                     reading.ph,
                     reading.nitrogen_mg_kg,
                     reading.phosphorus_mg_kg,
                     reading.potassium_mg_kg);
            (void)sd_storage_append_reading(&reading);
        } else {
            ESP_LOGW(TAG, "soil read failed: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

static void modem_task(void *arg)
{
    (void)arg;
    bool pulsed = false;

    while (true) {
        bool ready = false;
        esp_err_t err = sim7080_check_ready(&ready);

        if (!ready && !pulsed) {
            ESP_LOGW(TAG, "SIM7080 did not answer AT, pulsing PWRKEY once");
            (void)sim7080_power_key_pulse();
            pulsed = true;
        }

        app_state_set_modem_status(ready, err);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Soil Metrics ESP32-S3 display firmware starting");
    ESP_LOGW(TAG, "LCD RD, reset, and backlight behavior are unverified until hardware arrives");

    app_state_init();

    ESP_ERROR_CHECK(display_i80_init());
    ESP_ERROR_CHECK(touch_tsc2046_init());
    ESP_ERROR_CHECK(soil_sensor_init());
    ESP_ERROR_CHECK(sim7080_init());

    esp_err_t sd_err = sd_storage_init();
    app_state_set_sd_status(sd_err == ESP_OK, sd_err);

    lv_init();

    const size_t draw_buffer_pixels = BOARD_LCD_H_RES * BOARD_LCD_DRAW_LINES;
    lv_color_t *draw_buf_a = display_i80_alloc_draw_buffer(draw_buffer_pixels * sizeof(lv_color_t));
    lv_color_t *draw_buf_b = display_i80_alloc_draw_buffer(draw_buffer_pixels * sizeof(lv_color_t));
    if (draw_buf_a == NULL || draw_buf_b == NULL) {
        ESP_LOGE(TAG, "failed to allocate LVGL draw buffers");
        abort();
    }

    lv_display_t *display = lv_display_create(BOARD_LCD_H_RES, BOARD_LCD_V_RES);
    display_i80_register_lvgl(display);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(display, draw_buf_a, draw_buf_b, draw_buffer_pixels * sizeof(lv_color_t),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t *touch_indev = lv_indev_create();
    touch_tsc2046_register_lvgl(touch_indev);
    lv_indev_set_display(touch_indev, display);

    const esp_timer_create_args_t tick_timer_args = {
        .callback = lvgl_tick_cb,
        .name = "lvgl_tick",
    };
    esp_timer_handle_t tick_timer;
    ESP_ERROR_CHECK(esp_timer_create(&tick_timer_args, &tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(tick_timer, 1000));

    ui_init();

    xTaskCreate(lvgl_task, "lvgl", 4096, NULL, 5, NULL);
    xTaskCreate(soil_sensor_task, "soil_sensor", 4096, NULL, 4, NULL);
    xTaskCreate(modem_task, "modem", 4096, NULL, 3, NULL);
}
