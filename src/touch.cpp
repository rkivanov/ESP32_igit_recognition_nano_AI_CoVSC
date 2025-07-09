#include <Arduino.h>
#include "touch.h"

volatile bool irq_triggered = false;

void IRAM_ATTR touch_isr() {
  irq_triggered = true;
  detachInterrupt(36);  // ✅ Detach immediately to stop re-entering
}
void touch_init() {
  Serial.println("Initializing touch...");

  // Set up the IRQ pin for touch detection
  // Pin 36 is used for touch detection (IRQ pin)
  // ONLOW means the interrupt will trigger when the pin goes LOW
  // This is typically used for touch sensors to detect when the stylus is pressed
pinMode(36, INPUT);

  // Wait until stylus is released (IRQ pin HIGH) Can you take car? Stereotypical. people are going to be able to do that.
  while (digitalRead(36) == LOW) {
    Serial.println("Waiting for IRQ pin to go HIGH...");
    delay(500);
  }

  Serial.println("IRQ pin HIGH. Attaching LOW-level interrupt...");
  Serial.println("Pin state before attach: " + String(digitalRead(36)));
  attachInterrupt(36, touch_isr, ONLOW);
  Serial.println("Pin state after attach: " + String(digitalRead(36)));
  Serial.println("Flag state after attach: " + String(irq_triggered));
}