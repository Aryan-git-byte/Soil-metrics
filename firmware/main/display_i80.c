#include "display_i80.h"

#include <stddef.h>
#include "board_pins.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_lcd_io_i80.h"
#include "esp_lcd_panel_io.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LCD_CMD_DISPLAY_OFF 0x28
#define LCD_CMD_DISPLAY_ON 0x29
#define LCD_CMD_SLEEP_IN 0x10
#define LCD_CMD_SLEEP_OUT 0x11
#define LCD_CMD_COLUMN_ADDR 0x2A
#define LCD_CMD_PAGE_ADDR 0x2B
#define LCD_CMD_MEMORY_WRITE 0x2C
#define LCD_CMD_MEMORY_ACCESS 0x36
#define LCD_CMD_PIXEL_FORMAT 0x3A

static const char *TAG = "display_i80";

static esp_lcd_i80_bus_handle_t s_i80_bus;
static esp_lcd_panel_io_handle_t s_panel_io;
static lv_display_t *s_lvgl_display;
static display_rotation_t s_rotation = DISPLAY_ROTATION_90;

typedef struct {
    uint8_t cmd;
    const uint8_t *data;
    size_t data_len;
    uint32_t delay_ms;
} lcd_init_cmd_t;

static esp_err_t tx_param(uint8_t cmd, const uint8_t *data, size_t len)
{
    return esp_lcd_panel_io_tx_param(s_panel_io, cmd, data, len);
}

static esp_err_t tx_color(uint8_t cmd, const void *data, size_t len)
{
    return esp_lcd_panel_io_tx_color(s_panel_io, cmd, data, len);
}

static bool color_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    (void)panel_io;
    (void)edata;
    (void)user_ctx;

    if (s_lvgl_display != NULL) {
        lv_display_flush_ready(s_lvgl_display);
    }
    return false;
}

static esp_err_t send_init_sequence(void)
{
    static const uint8_t interface_mode[] = {0x00};
    static const uint8_t power1[] = {0x0E, 0x0E};
    static const uint8_t power2[] = {0x44};
    static const uint8_t vcom1[] = {0x00, 0x40, 0x00, 0x40};
    static const uint8_t madctl[] = {0x08};
    static const uint8_t col_addr[] = {0x00, 0x00, 0x01, 0xDF};
    static const uint8_t page_addr[] = {0x00, 0x00, 0x01, 0x3F};
    static const uint8_t pixel_format[] = {0x55};
    static const uint8_t display_func[] = {0x02, 0x02, 0x3B};
    static const uint8_t entry_mode[] = {0x06};
    static const uint8_t gamma_curve[] = {0x01};
    static const uint8_t gamma_pos[] = {
        0x0F, 0x1A, 0x0F, 0x18, 0x2F, 0x28, 0x20, 0x22,
        0x1F, 0x1B, 0x23, 0x37, 0x00, 0x07, 0x02,
    };
    static const uint8_t gamma_neg[] = {
        0x0F, 0x1B, 0x0F, 0x17, 0x33, 0x2C, 0x29, 0x2E,
        0x30, 0x30, 0x39, 0x3F, 0x00, 0x07, 0x03,
    };

    static const lcd_init_cmd_t init_cmds[] = {
        {LCD_CMD_DISPLAY_OFF, NULL, 0, 0},
        {0xB0, interface_mode, sizeof(interface_mode), 0},
        {0xC0, power1, sizeof(power1), 0},
        {0xC1, power2, sizeof(power2), 0},
        {0xC5, vcom1, sizeof(vcom1), 0},
        {LCD_CMD_MEMORY_ACCESS, madctl, sizeof(madctl), 0},
        {LCD_CMD_COLUMN_ADDR, col_addr, sizeof(col_addr), 0},
        {LCD_CMD_PAGE_ADDR, page_addr, sizeof(page_addr), 0},
        {LCD_CMD_PIXEL_FORMAT, pixel_format, sizeof(pixel_format), 0},
        {0x34, NULL, 0, 0},
        {0xB7, entry_mode, sizeof(entry_mode), 0},
        {0xB6, display_func, sizeof(display_func), 0},
        {0x26, gamma_curve, sizeof(gamma_curve), 0},
        {0xE0, gamma_pos, sizeof(gamma_pos), 0},
        {0xE1, gamma_neg, sizeof(gamma_neg), 0},
        {0x20, NULL, 0, 0},
        {LCD_CMD_SLEEP_OUT, NULL, 0, 120},
        {LCD_CMD_DISPLAY_ON, NULL, 0, 50},
    };

    for (size_t i = 0; i < sizeof(init_cmds) / sizeof(init_cmds[0]); ++i) {
        ESP_RETURN_ON_ERROR(tx_param(init_cmds[i].cmd, init_cmds[i].data, init_cmds[i].data_len), TAG,
                            "LCD init command 0x%02X failed", init_cmds[i].cmd);
        if (init_cmds[i].delay_ms > 0) {
            vTaskDelay(pdMS_TO_TICKS(init_cmds[i].delay_ms));
        }
    }

    return display_i80_set_rotation(s_rotation);
}

esp_err_t display_i80_init(void)
{
    ESP_LOGI(TAG, "initializing 16-bit i80 LCD bus");

    const esp_lcd_i80_bus_config_t bus_config = {
        .dc_gpio_num = BOARD_LCD_DC,
        .wr_gpio_num = BOARD_LCD_WR,
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .data_gpio_nums = {
            BOARD_LCD_DB0,
            BOARD_LCD_DB1,
            BOARD_LCD_DB2,
            BOARD_LCD_DB3,
            BOARD_LCD_DB4,
            BOARD_LCD_DB5,
            BOARD_LCD_DB6,
            BOARD_LCD_DB7,
            BOARD_LCD_DB8,
            BOARD_LCD_DB9,
            BOARD_LCD_DB10,
            BOARD_LCD_DB11,
            BOARD_LCD_DB12,
            BOARD_LCD_DB13,
            BOARD_LCD_DB14,
            BOARD_LCD_DB15,
        },
        .bus_width = 16,
        .max_transfer_bytes = BOARD_LCD_H_RES * BOARD_LCD_DRAW_LINES * sizeof(uint16_t),
        .dma_burst_size = 64,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_i80_bus(&bus_config, &s_i80_bus), TAG, "failed to create i80 bus");

    const esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = BOARD_LCD_CS,
        .pclk_hz = BOARD_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .on_color_trans_done = color_trans_done_cb,
        .flags = {
            .pclk_active_neg = 0,
            .pclk_idle_low = 0,
        },
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_i80(s_i80_bus, &io_config, &s_panel_io), TAG,
                        "failed to create i80 panel IO");

    return send_init_sequence();
}

void *display_i80_alloc_draw_buffer(size_t size_bytes)
{
    return esp_lcd_i80_alloc_draw_buffer(s_panel_io, size_bytes, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
}

void display_i80_register_lvgl(lv_display_t *display)
{
    s_lvgl_display = display;
    lv_display_set_flush_cb(display, display_i80_flush);
}

void display_i80_flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    const uint16_t x0 = (uint16_t)area->x1;
    const uint16_t y0 = (uint16_t)area->y1;
    const uint16_t x1 = (uint16_t)area->x2;
    const uint16_t y1 = (uint16_t)area->y2;
    const uint8_t caset[] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
    const uint8_t paset[] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};
    const size_t color_bytes = (size_t)(x1 - x0 + 1) * (size_t)(y1 - y0 + 1) * sizeof(uint16_t);

    esp_err_t err = tx_param(LCD_CMD_COLUMN_ADDR, caset, sizeof(caset));
    if (err == ESP_OK) {
        err = tx_param(LCD_CMD_PAGE_ADDR, paset, sizeof(paset));
    }
    if (err == ESP_OK) {
        err = tx_color(LCD_CMD_MEMORY_WRITE, px_map, color_bytes);
    }

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "flush failed: %s", esp_err_to_name(err));
        lv_display_flush_ready(display);
    }
}

esp_err_t display_i80_set_rotation(display_rotation_t rotation)
{
    uint8_t madctl = 0x48;

    switch (rotation) {
    case DISPLAY_ROTATION_0:
        madctl = 0x48;
        break;
    case DISPLAY_ROTATION_90:
        madctl = 0xE8;
        break;
    case DISPLAY_ROTATION_180:
        madctl = 0x88;
        break;
    case DISPLAY_ROTATION_270:
        madctl = 0x28;
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_ERROR(tx_param(LCD_CMD_MEMORY_ACCESS, &madctl, sizeof(madctl)), TAG, "rotation failed");
    s_rotation = rotation;
    return ESP_OK;
}

esp_err_t display_i80_set_sleep(bool sleep)
{
    ESP_RETURN_ON_ERROR(tx_param(sleep ? LCD_CMD_SLEEP_IN : LCD_CMD_SLEEP_OUT, NULL, 0), TAG, "sleep command failed");
    vTaskDelay(pdMS_TO_TICKS(sleep ? 5 : 120));
    return ESP_OK;
}

esp_err_t display_i80_display_on(bool on)
{
    return tx_param(on ? LCD_CMD_DISPLAY_ON : LCD_CMD_DISPLAY_OFF, NULL, 0);
}
