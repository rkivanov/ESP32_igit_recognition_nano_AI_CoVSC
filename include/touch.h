#pragma once
#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
void touch_init();
void IRAM_ATTR touch_isr();
extern volatile bool touch_event;
extern XPT2046_Touchscreen ts;