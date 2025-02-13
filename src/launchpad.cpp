#include "launchpad.h"
#include <Arduino.h>

void launchpad::setup() {
  Serial.println("Launchpad!");
}

// Example function definition
int example1(int x, float y, bool z) {
  return z ? x + y : x - y;
}