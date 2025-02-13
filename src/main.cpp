#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"
#include "geartrain.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  launchpad::setup();
  drummer::setup();
  geartrain::setup();
}

void loop() {
  Serial.print(".");
  delay(1000);
}