#pragma once
void mqtt_setup();
void mqtt_loop();
void mqtt_publish_digit(const uint8_t* data, size_t len);
void mqtt_set_callback(void (*callback)(char* topic, byte* payload, unsigned int length));