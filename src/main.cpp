#include <Arduino.h>
#include "wifi_comm.h"
//#include "mqtt_comm.h"
//#include "display.h"
#include "touch.h"
//#include "ui.h"

void setup() {
    Serial.begin(115200);
    //wifi_connect();
    //mqtt_setup();
    //display_init();
    touch_init();   // Sets up interrupt for touch
    wifi_connect();
    //ui_init();
}

void loop() {
    //mqtt_loop();
    
    // Test MQTT publishing every 10 seconds - COMMENTED OUT AFTER SUCCESSFUL TEST
    // static unsigned long lastPublish = 0;
    // if (millis() - lastPublish > 10000) {
    //     String testMessage = "Hello from ESP32 at " + String(millis());
    //     mqtt_publish_digit((uint8_t*)testMessage.c_str(), testMessage.length());
    //     Serial.println("Published test message: " + testMessage);
    //     lastPublish = millis();
    // }
    if (irq_triggered) {
    irq_triggered = false;
    Serial.println(">>> LOW-level IRQ triggered!");
    attachInterrupt(36, touch_isr, ONLOW);
  }
  

  //Serial.println("IRQ pin = " + String(digitalRead(36)));
  delay(1000);
    //ui_loop();    // No touch polling here; handled by interrupt
}