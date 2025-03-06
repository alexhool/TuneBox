#include <Arduino.h>
#include "launchpad.h"
#include "drummer.h"

void setup() {
  Serial.begin(115200);
  Serial.println("TuneBox Setup...");
  launchpad::setup();
  drummer::setup();
}

void loop() {
  Serial.print(".");
  delay(1000);
}