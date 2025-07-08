#include "ui.h"
#include "touch.h"
#include "display.h"
#include "mqtt_comm.h"

void ui_init() {
    // Draw UI: draw area, buttons, labels
    Serial.println("UI initialized successfully");
}

void ui_loop() {
    extern volatile bool touch_event;
    if (touch_event) {
        touch_event = false;
        // Read touch, update draw area, handle buttons
        // If "Send" pressed: convert to 28x28, mqtt_publish_digit()
        // If "Clear" pressed: display_clear_area()
    }
}