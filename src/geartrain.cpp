#include "geartrain.h"
#include <Arduino.h>

void geartrain::setup() {
  Serial.println("Gear Train!");
}

// Example function definition
int example3(int x, float y, bool z) {
  return z ? x + y : x - y;
}