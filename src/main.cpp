#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"

void setup() {
  Serial.begin(921600);
  Serial.println("\n--TuneBox Setup--");
  drummer::setup();
  launchpad::setup();
  Serial.println("\n--Starting Program--");
}

void loop() {
  drummer::loop();
  launchpad::loop();
  delay(10);
}