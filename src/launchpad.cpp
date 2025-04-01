#include "launchpad.h"
#include <Arduino.h>

SerLCD launchpad::lcd;

const uint8_t speaker = 3;
const uint8_t playButton = 12;
const uint8_t noteButtons[7] = {13, 18, 19, 20, 21, 22, 23}; //PINS: C D E F G A B
const uint16_t pianoNotes[7] = {262, 294, 330, 349, 392, 440, 494}; // C4 D4 E4 F4 G4 A4 B4

int8_t gameMode = 0; // 0 - Idle, 1 - Playing Notes, 2 - Game
static bool once = false;

void launchpad::setup(void) {
  Serial.println("Launchpad Setup");

  Serial.print("Initializing Buttons...");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(playButton, INPUT);
  pinMode(speaker, OUTPUT);
  for (int8_t i = 0; i < 7; i++) {
    pinMode(noteButtons[i], INPUT);
  }
  Serial.println(" Done");

  Serial.print("Initializing LCD...");
  Wire.begin(5, 6);
  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(3);
  lcd.clear();
  //lcd.print("Press PLAY");
  Serial.println(" Done");
}

void launchpad::loop(void) {
  if (digitalRead(playButton) == HIGH) {
    Serial.println("Game Mode");
    startGame();
  } else {
    Serial.println("Idle Mode");
    idleMode(); // Just a playable keyboard now
  }
}

void launchpad::idleMode() {
  for (int8_t i = 0; i < 7; i++) {
    if (digitalRead(noteButtons[i]) == HIGH) {
      tone(speaker, pianoNotes[i], 500);
      noTone(speaker);
    }
    if (!once) {
      lcd.clear();
      lcd.print("Play Any Note");
      once = true;
    }
  }
}

bool launchpad::waitForInput(int correctNote) {
  while (true) {
    for (int8_t i = 0; i < 7; i++) {
      if (digitalRead(noteButtons[i]) == HIGH) {
          tone(speaker, pianoNotes[i], 500);
          noTone(speaker);
        if (i == correctNote) {
          return true;
        } else { 
          return false; 
        }
      }
    }
  }
  return false;
}

void launchpad::startGame(void) {
  once = false;
  lcd.clear();
  lcd.print("Tune Box Game");
  delay(1000);

  for (int8_t i = 0; i < 3; i++) {
    lcd.clear();
    char notes[8] = "CDEFGAB";
    int sequence[3] = {random(7), random(7), random(7)};
    lcd.print("Play: ");
    for (int8_t i = 0; i < 3; i++){
      lcd.print(notes[sequence[i]]);
    }
    delay(1000);
    for (int8_t i = 0; i < 3; i++){
      if (waitForInput(sequence[i])){
        delay(1000);
      } else {
        lcd.clear();
        lcd.print("Game Over");
        delay(1000);
        lcd.clear();
        return; 
      }
    }
   }
   lcd.clear();
   lcd.print("You Win!");
   delay(1000);
}