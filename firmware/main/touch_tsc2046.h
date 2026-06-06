#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "lvgl.h"

typedef struct {
    bool pressed;
    uint16_t x;
    uint16_t y;
    uint16_t raw_x;
    uint16_t raw_y;
    uint16_t raw_z;
} touch_sample_t;

esp_err_t touch_tsc2046_init(void);
bool touch_tsc2046_read(touch_sample_t *sample);
void touch_tsc2046_register_lvgl(lv_indev_t *indev);
void touch_tsc2046_lvgl_read(lv_indev_t *indev, lv_indev_data_t *data);
