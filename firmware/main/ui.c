#include "ui.h"

#include <stdbool.h>
#include <stdio.h>
#include "app_state.h"
#include "board_pins.h"
#include "esp_err.h"

static lv_obj_t *s_touch_label;
static lv_obj_t *s_status_label;
static lv_obj_t *s_sensor_labels[7];

static lv_obj_t *create_label(lv_obj_t *parent, const char *text, int32_t col, int32_t row, int32_t col_span)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_set_style_text_font(label, LV_FONT_DEFAULT, 0);
    lv_obj_set_grid_cell(label, LV_GRID_ALIGN_START, col, col_span, LV_GRID_ALIGN_CENTER, row, 1);
    return label;
}

static void create_color_tile(lv_obj_t *parent, lv_color_t color, int32_t col, int32_t row)
{
    lv_obj_t *tile = lv_obj_create(parent);
    lv_obj_remove_style_all(tile);
    lv_obj_set_style_bg_color(tile, color, 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_grid_cell(tile, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);
}

static void ui_update_timer_cb(lv_timer_t *timer)
{
    (void)timer;

    soil_reading_t reading;
    peripheral_status_t status;
    app_state_get_soil_reading(&reading);
    app_state_get_peripheral_status(&status);

    char text[96];
    snprintf(text, sizeof(text), "SD: %s  SIM7080: %s  Soil: %s",
             status.sd_mounted ? "mounted" : esp_err_to_name(status.sd_error),
             status.modem_ready ? "ready" : esp_err_to_name(status.modem_error),
             reading.valid ? "valid" : esp_err_to_name(reading.last_error));
    lv_label_set_text(s_status_label, text);

    if (!reading.valid) {
        for (size_t i = 0; i < sizeof(s_sensor_labels) / sizeof(s_sensor_labels[0]); ++i) {
            lv_label_set_text(s_sensor_labels[i], "--");
        }
        return;
    }

    snprintf(text, sizeof(text), "Moisture: %.1f %%", reading.moisture_percent);
    lv_label_set_text(s_sensor_labels[0], text);
    snprintf(text, sizeof(text), "Temp: %.1f C", reading.temperature_c);
    lv_label_set_text(s_sensor_labels[1], text);
    snprintf(text, sizeof(text), "EC: %u uS/cm", reading.ec_us_cm);
    lv_label_set_text(s_sensor_labels[2], text);
    snprintf(text, sizeof(text), "pH: %.1f", reading.ph);
    lv_label_set_text(s_sensor_labels[3], text);
    snprintf(text, sizeof(text), "N: %u mg/kg", reading.nitrogen_mg_kg);
    lv_label_set_text(s_sensor_labels[4], text);
    snprintf(text, sizeof(text), "P: %u mg/kg", reading.phosphorus_mg_kg);
    lv_label_set_text(s_sensor_labels[5], text);
    snprintf(text, sizeof(text), "K: %u mg/kg", reading.potassium_mg_kg);
    lv_label_set_text(s_sensor_labels[6], text);
}

void ui_init(void)
{
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x101820), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

    static int32_t cols[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static int32_t rows[] = {34, 34, 54, 32, 32, 32, 32, 32, 44, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(screen, cols, rows);
    lv_obj_set_style_pad_all(screen, 10, 0);
    lv_obj_set_style_pad_row(screen, 8, 0);
    lv_obj_set_style_pad_column(screen, 8, 0);

    (void)create_label(screen, "Soil Metrics ESP32-S3", 0, 0, 2);
    s_status_label = create_label(screen, "SD: --  SIM7080: --  Soil: --", 2, 0, 2);

    s_sensor_labels[0] = create_label(screen, "Moisture: --", 0, 1, 1);
    s_sensor_labels[1] = create_label(screen, "Temp: --", 1, 1, 1);
    s_sensor_labels[2] = create_label(screen, "EC: --", 2, 1, 1);
    s_sensor_labels[3] = create_label(screen, "pH: --", 3, 1, 1);

    create_color_tile(screen, lv_color_hex(0x000000), 0, 2);
    create_color_tile(screen, lv_color_hex(0xF80000), 1, 2);
    create_color_tile(screen, lv_color_hex(0x00A000), 2, 2);
    create_color_tile(screen, lv_color_hex(0x0040FF), 3, 2);

    s_sensor_labels[4] = create_label(screen, "N: --", 0, 3, 1);
    s_sensor_labels[5] = create_label(screen, "P: --", 1, 3, 1);
    s_sensor_labels[6] = create_label(screen, "K: --", 2, 3, 1);

    s_touch_label = create_label(screen, "Touch: waiting for raw samples", 0, 8, 4);

    lv_obj_t *border = lv_obj_create(screen);
    lv_obj_remove_style_all(border);
    lv_obj_set_style_border_width(border, 1, 0);
    lv_obj_set_style_border_color(border, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(border, LV_OPA_TRANSP, 0);
    lv_obj_set_size(border, BOARD_LCD_H_RES, BOARD_LCD_V_RES);
    lv_obj_align(border, LV_ALIGN_CENTER, 0, 0);
    lv_obj_remove_flag(border, LV_OBJ_FLAG_CLICKABLE);

    lv_timer_create(ui_update_timer_cb, 1000, NULL);
}

void ui_set_touch_sample(int32_t x, int32_t y, int32_t z, bool pressed)
{
    if (s_touch_label == NULL) {
        return;
    }

    char text[96];
    snprintf(text, sizeof(text), "Touch: %s  x=%ld y=%ld z=%ld", pressed ? "pressed" : "released",
             (long)x, (long)y, (long)z);
    lv_label_set_text(s_touch_label, text);
}
