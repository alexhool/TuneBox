#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"

void setup() {
  Serial.begin(921600);
  Serial.println("TuneBox Setup...");
  drummer::setup();
  launchpad::setup();
  Serial.println("Starting program...");
}

void loop() {
  drummer::loop();
  launchpad::loop();
  delay(10);
}