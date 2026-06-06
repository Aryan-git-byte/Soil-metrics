#pragma once

#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

esp_err_t rs485_modbus_init(void);
esp_err_t rs485_modbus_read_holding_registers(uint8_t slave_addr,
                                              uint16_t start_reg,
                                              uint16_t *registers,
                                              size_t register_count,
                                              uint32_t timeout_ms);
