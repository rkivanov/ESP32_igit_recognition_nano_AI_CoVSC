#include "touch.h"
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define TOUCH_CS 33
#define TOUCH_IRQ 36

XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
volatile bool touch_event = false;

void IRAM_ATTR touch_isr() {
    touch_event = true;
}

void touch_init() {
    ts.begin();
    ts.setRotation(1);
    pinMode(TOUCH_IRQ, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ), touch_isr, FALLING);
    Serial.println("Touchscreen initialized successfully");
}