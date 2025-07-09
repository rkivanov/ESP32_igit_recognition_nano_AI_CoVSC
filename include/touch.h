#pragma once
#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
void touch_init();
extern volatile bool touch_event;
extern XPT2046_Touchscreen ts;