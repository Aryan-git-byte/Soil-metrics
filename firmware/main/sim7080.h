#pragma once

#include <stdbool.h>
#include "esp_err.h"

esp_err_t sim7080_init(void);
esp_err_t sim7080_power_key_pulse(void);
esp_err_t sim7080_check_ready(bool *ready);
