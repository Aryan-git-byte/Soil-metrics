#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"

typedef struct {
    bool valid;
    float moisture_percent;
    float temperature_c;
    uint16_t ec_us_cm;
    float ph;
    uint16_t nitrogen_mg_kg;
    uint16_t phosphorus_mg_kg;
    uint16_t potassium_mg_kg;
    uint32_t sequence;
    int64_t updated_us;
    esp_err_t last_error;
} soil_reading_t;

typedef struct {
    bool sd_mounted;
    bool modem_ready;
    esp_err_t sd_error;
    esp_err_t modem_error;
} peripheral_status_t;

void app_state_init(void);
void app_state_set_soil_reading(const soil_reading_t *reading);
void app_state_get_soil_reading(soil_reading_t *reading);
void app_state_set_sd_status(bool mounted, esp_err_t error);
void app_state_set_modem_status(bool ready, esp_err_t error);
void app_state_get_peripheral_status(peripheral_status_t *status);
