#include <Arduino.h>
#include "cymbal.h"

VL53L0X cymbal::tof;
Servo cymbal::leftservo;
Servo cymbal::rightservo;

const uint8_t LEFTSERVO_PIN = 0;
const uint8_t RIGHTSERVO_PIN = 17;
const uint8_t LEFTSERVO_START = 0;
const uint8_t RIGHTSERVO_START = 180;
const uint8_t DISTANCE_THRESHOLD = 40;

void cymbal::setup(void) {
  Serial.println("Cymbal Buzz Setup");

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

void cymbal::loop(void) {
  uint16_t distance = tof.readRangeContinuousMillimeters();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("mm");

  if (distance < DISTANCE_THRESHOLD) {
    clap();
  }
}

void cymbal::clap(void) {
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
  playCymbal();
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
  playCymbal();
}

void cymbal::playCymbal(void) {
  Serial.println("Playing cymbal");

  int steps = 50;
  int stepDuration = 250 / steps;
  int freqStep = (1000 - 800) / steps;

  for (int i = 0; i < steps; i++) {
    uint16_t currentFreq = 1000 - (freqStep * i);
    tone(3, currentFreq, stepDuration);
    delay(stepDuration);
  }

  noTone(3);
}
