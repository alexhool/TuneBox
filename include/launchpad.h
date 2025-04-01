#ifndef LAUNCHPAD_H
#define LAUNCHPAD_H

#include <SerLCD.h>

namespace launchpad {
  extern SerLCD lcd;
  void setup(void);
  void loop(void);
  void idleMode(void);
  bool waitForInput(int);
  void startGame(void);
}

#endif