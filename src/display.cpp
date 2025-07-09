#include "display.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void display_init() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    
    // Show initialization message in center of screen
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.drawString("Display initialized", 80, 100, 2);
    tft.drawString("successfully!", 90, 120, 2);
    
    Serial.println("Display initialized successfully");
}

void display_show_digit(int digit) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("The digit is:", 10, 180, 2);
    tft.drawNumber(digit, 150, 180, 4);
}

void display_clear_area() {
    tft.fillRect(0, 0, 112, 112, TFT_BLACK);
}