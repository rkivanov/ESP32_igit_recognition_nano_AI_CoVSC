#include <Arduino.h>
#include "wifi_comm.h"
//#include "mqtt_comm.h"
//#include "display.h"
//#include "touch.h"
//#include "ui.h"

void setup() {
    Serial.begin(115200);
    wifi_connect();
    //mqtt_setup();
    //display_init();
    //touch_init();   // Sets up interrupt for touch
    //ui_init();
}

void loop() {
    //mqtt_loop();
    //ui_loop();    // No touch polling here; handled by interrupt
}