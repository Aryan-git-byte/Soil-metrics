#pragma once

#include <stdbool.h>
#include "lvgl.h"

void ui_init(void);
void ui_set_touch_sample(int32_t x, int32_t y, int32_t z, bool pressed);
