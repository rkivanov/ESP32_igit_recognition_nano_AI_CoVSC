#pragma once
#include <Arduino.h>

extern volatile bool irq_triggered;  // Flag to indicate if the touch interrupt was triggered

void touch_init();
void IRAM_ATTR touch_isr();
