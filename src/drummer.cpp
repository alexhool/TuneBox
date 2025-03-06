#include "drummer.h"
#include <Arduino.h>

VL53L0X drummer::tof;
Servo drummer::servo;

const int SERVO_PIN = 13;
const int SERVO_START_POS = 90;
const int SERVO_END_POS = 180;
const int DISTANCE_THRESHOLD = 80;

void drummer::setup() {
  Serial.println("|--Drummer Setup--|");

  // Initialize Servo
  Serial.print("Initializing Servo...");
  ESP32PWM::timerCount[0] = 4;
  ESP32PWM::allocateTimer(1);
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 1000, 2000);
  servo.write(SERVO_START_POS);
  Serial.println("Done");

  // Initialize ToF
  Serial.print("Initializing ToF...");
  Wire.begin(6, 7);
  tof.setTimeout(100); // gives up after 100ms
  if (!tof.init()) {
    Serial.println("Failed to boot ToF");
    while (1);
  }
  tof.setMeasurementTimingBudget(20000); // 20ms measurement time (default: 33ms)
  tof.startContinuous();
  Serial.println("Done");

  Serial.println("|-----------------|");
}

void drummer::start() {
  uint16_t distance = tof.readRangeContinuousMillimeters();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < DISTANCE_THRESHOLD) {
    Serial.println("Sweeping Servo");
    for (int pos = SERVO_START_POS; pos <= SERVO_END_POS; pos++) {
      servo.write(pos);
      delay(15);
    }
    delay(500);
    for (int pos = SERVO_END_POS; pos >= SERVO_START_POS; pos--) {
      servo.write(pos);
      delay(15);
    }
  }
}