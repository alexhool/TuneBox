#ifndef DRUMMER_H
#define DRUMMER_H

#include <VL53L0X.h>
#include <ESP32Servo.h>

namespace drummer {
  extern VL53L0X tof;
  extern Servo leftservo;
  extern Servo rightservo;
  void setup();
  void loop();
}

#endif