#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"

void setup() {
  Serial.begin(115200);
  // Serial.println("\n--TuneBox Setup--");
  Wire.begin(6, 7);
  // drummer::setup();
  launchpad::setup();
  Serial.println("\n--Starting Program--");
}

void loop() {
  // drummer::loop();
  launchpad::loop();
}