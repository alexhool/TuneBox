#include "launchpad.h"
#include <Arduino.h>

SerLCD launchpad::lcd;

const uint8_t speaker = 3;
const uint8_t playButton = 12;
const uint8_t noteButtons[7] = {13, 18, 19, 20, 21, 23, 22}; //PINS: C D E F G A B
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
    idleMode(); // Just a playable keyboard now
  }
}

void launchpad::idleMode() {
  for (int8_t i = 0; i < 7; i++) {
    if (digitalRead(noteButtons[i]) == HIGH) {
      Serial.println(i);
      //tone(speaker, pianoNotes[i], 500);
      noTone(speaker);
      lcd.setCursor(0, 1);
      lcd.print("You Played: ");
      lcd.print("CDEFGAB"[i]);
    }
    if (!once) {
      lcd.clear();
      lcd.print("Play Any Note!");
      once = true;
    }
  }
}

bool launchpad::waitForInput(int correctNote) {
  unsigned long start = millis();
  const unsigned long timeout = 10000; // 10 second timeout
  
  while (millis() - start < timeout) {
    for (int8_t i = 0; i < 7; i++) {
      if (digitalRead(noteButtons[i]) == HIGH) {
        // tone(speaker, pianoNotes[i], 500);
        noTone(speaker);

        lcd.print("You Played: ");
        lcd.print("CDEFGAB"[i]);

        delay(300);
        while(digitalRead(noteButtons[i]) == HIGH) {
          delay(10);
        }
        if (i == correctNote) {
          Serial.println("Correct");
          return true;
        } else {
          Serial.println("Wrong");
          return false; 
        }
      }
    }
    delay(10);
  }

  lcd.setCursor(0, 1);
  lcd.print("Time's up!");
  return false;
}

void launchpad::startGame(void) {
  once = false;
  lcd.clear();
  lcd.print("Tune Box Game");
  delay(1000);

  lcd.clear();
  char notes[8] = "CDEFGAB";
  int sequence[3] = {0, 1, 2};

  lcd.print("Memorize and");
  lcd.setCursor(0, 1);
  lcd.print("Play: ");
  for (int8_t j = 0; j < 3; j++) {
    lcd.print(notes[sequence[j]]);
  }

  lcd.setCursor(12, 1);
  lcd.print("( )");
  for (int8_t i = 5; i > 0; i--) {
    lcd.setCursor(13, 1);
    lcd.print(i);
    delay(1000);
  }

  for (int8_t note = 0; note < 3; note++) {
    lcd.clear();
    if (waitForInput(sequence[note])) {
      delay(500);
    } else {
      lcd.clear();
      lcd.print("Game Over");
      delay(2000);
      lcd.clear();
      return; 
    }
  }

  lcd.clear();
  lcd.print("You Win!");
  delay(2000);
}