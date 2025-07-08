#include "mqtt_comm.h"
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    // Handle incoming MQTT messages
}

void mqtt_setup() {
    client.setServer("192.168.1.20", 1883);
    client.setCallback(mqtt_callback);
    while (!client.connected()) {
        client.connect("ESP32Client");
    }
}

void mqtt_loop() {
    client.loop();
}

void mqtt_publish_digit(const uint8_t* data, size_t len) {
    client.publish("digit_topic", data, len);
}

void mqtt_set_callback(void (*callback)(char*, byte*, unsigned int)) {
    client.setCallback(callback);
}