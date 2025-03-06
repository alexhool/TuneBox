#ifndef DRUMMER_H
#define DRUMMER_H

#include <VL53L0X.h>
#include <ESP32Servo.h>

namespace drummer {
  extern VL53L0X tof;
  extern Servo servo;
  void setup();
  void start();
}

#endif