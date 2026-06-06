#pragma once

#include "app_state.h"
#include "esp_err.h"

esp_err_t sd_storage_init(void);
esp_err_t sd_storage_append_reading(const soil_reading_t *reading);
