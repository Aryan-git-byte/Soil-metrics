#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"
#include "lvgl.h"

typedef enum {
    DISPLAY_ROTATION_0 = 0,
    DISPLAY_ROTATION_90,
    DISPLAY_ROTATION_180,
    DISPLAY_ROTATION_270,
} display_rotation_t;

esp_err_t display_i80_init(void);
void *display_i80_alloc_draw_buffer(size_t size_bytes);
void display_i80_register_lvgl(lv_display_t *display);
void display_i80_flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);
esp_err_t display_i80_set_rotation(display_rotation_t rotation);
esp_err_t display_i80_set_sleep(bool sleep);
esp_err_t display_i80_display_on(bool on);
