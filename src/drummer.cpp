#include "drummer.h"
#include <Arduino.h>

Adafruit_VL53L0X drummer::lox = Adafruit_VL53L0X();
Servo drummer::servo;

void drummer::setup() {
  Serial.print("Initializing Drummer...");
  // Initialize ToF
  if (!lox.begin()) {
    Serial.println("Failed to boot ToF");
    while(1);
  }
  lox.startRangeContinuous();

  Serial.println("Finished");
}

void drummer::start() {
  if (lox.isRangeComplete()) {
    uint16_t distance = lox.readRange();
    Serial.print("Distance in mm: ");
    Serial.println(distance);
  }
}