#include "soil_sensor.h"

#include <stdint.h>
#include "esp_timer.h"
#include "rs485_modbus.h"

#define SOIL_SENSOR_SLAVE_ADDR 0x01
#define SOIL_SENSOR_START_REG 0x0000
#define SOIL_SENSOR_REG_COUNT 7
#define SOIL_SENSOR_TIMEOUT_MS 1000

esp_err_t soil_sensor_init(void)
{
    return rs485_modbus_init();
}

esp_err_t soil_sensor_read(soil_reading_t *reading)
{
    static uint32_t sequence;
    uint16_t regs[SOIL_SENSOR_REG_COUNT] = {0};
    esp_err_t err = rs485_modbus_read_holding_registers(SOIL_SENSOR_SLAVE_ADDR,
                                                        SOIL_SENSOR_START_REG,
                                                        regs,
                                                        SOIL_SENSOR_REG_COUNT,
                                                        SOIL_SENSOR_TIMEOUT_MS);

    reading->sequence = ++sequence;
    reading->updated_us = esp_timer_get_time();
    reading->last_error = err;
    reading->valid = (err == ESP_OK);

    if (err != ESP_OK) {
        return err;
    }

    reading->moisture_percent = regs[0] / 10.0f;
    reading->temperature_c = (int16_t)regs[1] / 10.0f;
    reading->ec_us_cm = regs[2];
    reading->ph = regs[3] / 10.0f;
    reading->nitrogen_mg_kg = regs[4];
    reading->phosphorus_mg_kg = regs[5];
    reading->potassium_mg_kg = regs[6];

    return ESP_OK;
}
