#include "launchpad.h"
#include <Arduino.h>

SerLCD launchpad::lcd;

const uint8_t speaker = 19;
const uint8_t playButton = 7;
const uint8_t bGuitarButton = 8;
const uint8_t noteButtons[7] = {2, 3, 15, 23, 22, 21, 20}; //PINS: C D E F G A B

int8_t gameMode = 0; // 0 - Idle, 1 - Playing Notes, 2 - Game
//bool guitarMode = false;
int correctSequences = 0;
static bool once = false;

const uint16_t pianoNotes[7] = {262, 294, 330, 349, 392, 440, 494}; // C4 D4 E4 F4 G4 A4 B4
const uint16_t guitarNotes[7] = {262, 262, 262, 262, 262, 262, 262}; // Guitar equivalents

void launchpad::setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(playButton, INPUT);
  pinMode(bGuitarButton, INPUT);
  pinMode(speaker, OUTPUT);
  for (int8_t i = 0; i < 7; i++) {
    pinMode(noteButtons[i], INPUT);
  }

  Wire.begin(5, 6);
  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(3);
  lcd.clear();
  //lcd.print("Press PLAY");
}

void launchpad::loop(void) {
  if (digitalRead(playButton) == HIGH) {
    startGame();
  } else {
    idleMode(); // Just a playable keyboard now
  }
}

void launchpad::idleMode() {
  for (int8_t i = 0; i < 7; i++) {
    if (digitalRead(noteButtons[i]) == HIGH) {
      if (digitalRead(bGuitarButton) == LOW) {
        tone(speaker, guitarNotes[i], 500);
      } else {
        tone(speaker, pianoNotes[i], 500);
      }
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