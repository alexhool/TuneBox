#include <Arduino.h>
#include "keyboard.h"
#include "cymbal.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n--TuneBox Setup--");
  Wire.begin(6, 7);
  cymbal::setup();
  keyboard::setup();
  Serial.println("\n--Starting Program--");
  delay(2000);
}

void loop() {
  cymbal::loop();
  keyboard::loop();
}