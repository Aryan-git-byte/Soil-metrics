#include "app_state.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static SemaphoreHandle_t s_lock;
static soil_reading_t s_soil_reading;
static peripheral_status_t s_status;

void app_state_init(void)
{
    s_lock = xSemaphoreCreateMutex();
    s_soil_reading.last_error = ESP_ERR_INVALID_STATE;
    s_status.sd_error = ESP_ERR_INVALID_STATE;
    s_status.modem_error = ESP_ERR_INVALID_STATE;
}

static void lock_state(void)
{
    if (s_lock != NULL) {
        xSemaphoreTake(s_lock, portMAX_DELAY);
    }
}

static void unlock_state(void)
{
    if (s_lock != NULL) {
        xSemaphoreGive(s_lock);
    }
}

void app_state_set_soil_reading(const soil_reading_t *reading)
{
    lock_state();
    s_soil_reading = *reading;
    unlock_state();
}

void app_state_get_soil_reading(soil_reading_t *reading)
{
    lock_state();
    *reading = s_soil_reading;
    unlock_state();
}

void app_state_set_sd_status(bool mounted, esp_err_t error)
{
    lock_state();
    s_status.sd_mounted = mounted;
    s_status.sd_error = error;
    unlock_state();
}

void app_state_set_modem_status(bool ready, esp_err_t error)
{
    lock_state();
    s_status.modem_ready = ready;
    s_status.modem_error = error;
    unlock_state();
}

void app_state_get_peripheral_status(peripheral_status_t *status)
{
    lock_state();
    *status = s_status;
    unlock_state();
}
