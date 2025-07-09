#include "ui.h"
#include "touch.h"
#include "display.h"
#include "mqtt_comm.h"
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

extern XPT2046_Touchscreen ts;
extern TFT_eSPI tft;

// UI layout constants
#define DRAW_AREA_X 10
#define DRAW_AREA_Y 10
#define DRAW_AREA_SIZE 112
#define CLEAR_BTN_X 140
#define CLEAR_BTN_Y 30
#define CLEAR_BTN_W 60
#define CLEAR_BTN_H 30
#define SEND_BTN_X 140
#define SEND_BTN_Y 70
#define SEND_BTN_W 60
#define SEND_BTN_H 30

void ui_init() {
    // Clear screen and draw UI elements
    tft.fillScreen(TFT_BLACK);
    
    // Draw drawing area border
    tft.drawRect(DRAW_AREA_X-1, DRAW_AREA_Y-1, DRAW_AREA_SIZE+2, DRAW_AREA_SIZE+2, TFT_WHITE);
    tft.fillRect(DRAW_AREA_X, DRAW_AREA_Y, DRAW_AREA_SIZE, DRAW_AREA_SIZE, TFT_BLACK);
    
    // Draw Clear button
    tft.fillRect(CLEAR_BTN_X, CLEAR_BTN_Y, CLEAR_BTN_W, CLEAR_BTN_H, TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("CLEAR", CLEAR_BTN_X+10, CLEAR_BTN_Y+8, 2);
    
    // Draw Send button
    tft.fillRect(SEND_BTN_X, SEND_BTN_Y, SEND_BTN_W, SEND_BTN_H, TFT_GREEN);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("SEND", SEND_BTN_X+15, SEND_BTN_Y+8, 2);
    
    // Draw instruction text
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Draw digit here:", DRAW_AREA_X, DRAW_AREA_Y + DRAW_AREA_SIZE + 10, 1);
    
    Serial.println("UI initialized successfully");
}

void ui_loop() {
    // Use the correct method from Random Nerd Tutorials
    if (ts.tirqTouched() && ts.touched()) {
        TS_Point p = ts.getPoint();
        
        // Use the correct coordinate mapping from the working example
        int x = map(p.x, 200, 3700, 1, 320);
        int y = map(p.y, 240, 3800, 1, 240);
        
        // Debug: Print coordinates
        Serial.println("Touch: " + String(x) + "," + String(y) + " (raw: " + String(p.x) + "," + String(p.y) + ")");
        
        // Check if touch is in drawing area
        if (x >= DRAW_AREA_X && x <= DRAW_AREA_X + DRAW_AREA_SIZE &&
            y >= DRAW_AREA_Y && y <= DRAW_AREA_Y + DRAW_AREA_SIZE) {
            // Draw pixel in drawing area
            tft.fillCircle(x, y, 2, TFT_WHITE);
            Serial.println("Drawing at: " + String(x) + "," + String(y));
        }
        
        // Check if Clear button pressed
        else if (x >= CLEAR_BTN_X && x <= CLEAR_BTN_X + CLEAR_BTN_W &&
                 y >= CLEAR_BTN_Y && y <= CLEAR_BTN_Y + CLEAR_BTN_H) {
            // Clear drawing area
            tft.fillRect(DRAW_AREA_X, DRAW_AREA_Y, DRAW_AREA_SIZE, DRAW_AREA_SIZE, TFT_BLACK);
            Serial.println("Clear button pressed");
        }
        
        // Check if Send button pressed
        else if (x >= SEND_BTN_X && x <= SEND_BTN_X + SEND_BTN_W &&
                 y >= SEND_BTN_Y && y <= SEND_BTN_Y + SEND_BTN_H) {
            // Send drawing data via MQTT
            String message = "Digit drawing sent at " + String(millis());
            mqtt_publish_digit((uint8_t*)message.c_str(), message.length());
            Serial.println("Send button pressed - digit sent via MQTT");
        }
        
        // Debug: Show which area was touched
        else {
            Serial.println("Touch outside defined areas");
        }
        
        // Small delay to prevent multiple rapid touches
        delay(100);
    }
}