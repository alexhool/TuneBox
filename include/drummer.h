#ifndef DRUMMER_H
#define DRUMMER_H

#include <Adafruit_VL53L0X.h>
#include <ESP32Servo.h>

namespace drummer {
  extern Adafruit_VL53L0X lox;
  extern Servo servo;
  void setup();
  void start();
}

#endif