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
  Serial.print("Starting program...");
  drummer::start();
  delay(1000);
}