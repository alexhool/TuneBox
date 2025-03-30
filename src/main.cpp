#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"

void setup() {
  Serial.begin(921600);
  Serial.println("TuneBox Setup...");
  launchpad::setup();
  drummer::setup();
  Serial.println("Starting program...");
}

void loop() {
  drummer::start();
  delay(1000);
}