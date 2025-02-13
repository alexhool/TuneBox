#include "drummer.h"
#include <Arduino.h>

void drummer::setup() {
  Serial.println("Drummer!");
}

// Example function definition
int example2(int x, float y, bool z) {
  return z ? x + y : x - y;
}