#pragma once

#include "app_state.h"
#include "esp_err.h"

esp_err_t soil_sensor_init(void);
esp_err_t soil_sensor_read(soil_reading_t *reading);
