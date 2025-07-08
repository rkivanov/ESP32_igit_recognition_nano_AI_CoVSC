#include "display.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void display_init() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

void display_show_digit(int digit) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("The digit is:", 10, 180, 2);
    tft.drawNumber(digit, 150, 180, 4);
}

void display_clear_area() {
    tft.fillRect(0, 0, 112, 112, TFT_BLACK);
}