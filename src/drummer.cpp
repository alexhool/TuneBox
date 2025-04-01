#include "drummer.h"
#include <Arduino.h>

VL53L0X drummer::tof;
Servo drummer::leftservo;
Servo drummer::rightservo;

const uint8_t LEFTSERVO_PIN = 0;
const uint8_t RIGHTSERVO_PIN = 15;
const uint8_t LEFTSERVO_START = 0;
const uint8_t RIGHTSERVO_START = 180;
const uint8_t DISTANCE_THRESHOLD = 80;

void drummer::setup(void) {
  Serial.println("Drummer Setup");

  // Initialize Servo
  Serial.print("Initializing Servos...");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  leftservo.setPeriodHertz(50);
  leftservo.attach(LEFTSERVO_PIN, 1000, 2000);
  leftservo.write(LEFTSERVO_START);
  rightservo.setPeriodHertz(50);
  rightservo.attach(RIGHTSERVO_PIN, 1000, 2000);
  rightservo.write(RIGHTSERVO_START);
  Serial.println(" Done");

  // Initialize ToF
  Serial.print("Initializing ToF...");
  tof.setTimeout(100); // gives up after 100ms
  while (!tof.init()) {
    Serial.print(".");
    delay(500);
  }
  tof.setMeasurementTimingBudget(20000); // 20ms measurement time (default: 33ms)
  tof.startContinuous();
  Serial.println(" Done");
}

void drummer::loop(void) {
  uint16_t distance = tof.readRangeContinuousMillimeters();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("mm");

  if (distance < DISTANCE_THRESHOLD) {
    Serial.println("Clapping twice");
    // First clap
    for (int8_t i = 0; i <= 45; i++) {
      leftservo.write(LEFTSERVO_START + i);
      rightservo.write(RIGHTSERVO_START - i);
      delay(10);
    }
    // Return to start
    for (int8_t i = 45; i >= 0; i--) {
      leftservo.write(LEFTSERVO_START + i);
      rightservo.write(RIGHTSERVO_START - i);
      delay(10);
    }
    delay(500);
    // Second clap
    for (int8_t i = 0; i <= 45; i++) {
      leftservo.write(LEFTSERVO_START + i);
      rightservo.write(RIGHTSERVO_START - i);
      delay(19);
    }
    // Return to start
    for (int8_t i = 45; i >= 0; i--) {
      leftservo.write(LEFTSERVO_START + i);
      rightservo.write(RIGHTSERVO_START - i);
      delay(10);
    }
  }
}