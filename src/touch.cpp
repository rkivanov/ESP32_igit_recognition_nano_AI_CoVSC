#include "touch.h"
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
volatile bool touch_event = false;

void IRAM_ATTR touch_isr() {
    touch_event = true;
}

void touch_init() {
    // Start the SPI for the touchscreen and init the touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    ts.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    ts.setRotation(1);
    
    // Test if touchscreen is responding properly
    if (ts.touched()) {
        Serial.println("Warning: Touchscreen shows as touched during initialization");
    }
    
    pinMode(XPT2046_IRQ, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(XPT2046_IRQ), touch_isr, FALLING);
    Serial.println("Touchscreen initialized successfully");
    
    // Debug: Check IRQ pin state
    Serial.println("Touch IRQ pin state: " + String(digitalRead(XPT2046_IRQ)));
}