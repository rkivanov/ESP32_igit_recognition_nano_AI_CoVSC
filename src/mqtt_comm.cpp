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
    
    int attempts = 0;
    while (!client.connected() && attempts < 10) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("MQTT connected");
            break;
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
            attempts++;
        }
    }
    
    if (!client.connected()) {
        Serial.println("Failed to connect to MQTT broker after 10 attempts");
    }
}

void mqtt_loop() {
    if (!client.connected()) {
        Serial.println("MQTT disconnected, attempting to reconnect...");
        if (client.connect("ESP32Client")) {
            Serial.println("MQTT reconnected");
        } else {
            Serial.print("MQTT reconnection failed, rc=");
            Serial.println(client.state());
        }
    }
    client.loop();
}

void mqtt_publish_digit(const uint8_t* data, size_t len) {
    client.publish("digit_topic", data, len);
}

void mqtt_set_callback(void (*callback)(char*, byte*, unsigned int)) {
    client.setCallback(callback);
}