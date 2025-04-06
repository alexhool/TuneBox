#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SerLCD.h>

namespace keyboard {
  extern SerLCD lcd;
  void setup(void);
  void loop(void);
  void idleMode(void);
  bool waitForInput(int);
  void startGame(void);
}

#endif