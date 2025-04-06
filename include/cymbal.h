#ifndef CYMBAL_H
#define CYMBAL_H

#include <VL53L0X.h>
#include <ESP32Servo.h>

namespace cymbal {
  extern VL53L0X tof;
  extern Servo leftservo;
  extern Servo rightservo;
  void setup(void);
  void loop(void);
  void clap(void);
  void playCymbal(void);
}

#endif