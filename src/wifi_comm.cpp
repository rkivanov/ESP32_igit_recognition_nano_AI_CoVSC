#include "wifi_comm.h"
#include <WiFi.h>

const char* ssid = "Auto_Platforms";
const char* password = "qazwsxed";


void wifi_connect() {
    // ✅ Configure WiFi to be interrupt-friendly
    //WiFi.mode(WIFI_STA);              // Station mode only
    WiFi.setSleep(false);             // Disable WiFi sleep mode
    //WiFi.setAutoReconnect(false);     // Disable auto-reconnect

    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Signal Strength: ");
    Serial.println(WiFi.RSSI());
}