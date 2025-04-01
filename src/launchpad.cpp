#include "launchpad.h"
#include <Arduino.h>

SerLCD launchpad::lcd;

#define SDA 5
#define SCL 6
#define DELAY_INTERVAL 250
#define SPEAKER 19

#define PIANONOTE_C 262 //C4
#define PIANONOTE_D 294 //D4
#define PIANONOTE_E 330 //E4
#define PIANONOTE_F 349 //F4
#define PIANONOTE_G 392 //G4
#define PIANONOTE_A 440 //A4
#define PIANONOTE_B 494 //B4

#define GUITARNOTE_C 262
#define GUITARNOTE_D 262
#define GUITARNOTE_E 262
#define GUITARNOTE_F 262
#define GUITARNOTE_G 262
#define GUITARNOTE_A 262
#define GUITARNOTE_B 262

const int playButton = 7;
const int bGuitarButton = 8;
const int noteButtons[7] = {2, 3, 15, 23, 22, 21, 20}; //PINS: C D E F G A B

int gameMode = 0; // 0 - Idle, 1 - Playing Notes, 2 - Game
//bool guitarMode = false;
int correctSequences = 0;
static bool once = false;

const int pianoNotes[7] = {PIANONOTE_C, PIANONOTE_D, PIANONOTE_E, PIANONOTE_F, PIANONOTE_G, PIANONOTE_A, PIANONOTE_B}; // C D E F G A B
const int guitarNotes[7] = {GUITARNOTE_C, GUITARNOTE_D, GUITARNOTE_E, GUITARNOTE_F, GUITARNOTE_G, GUITARNOTE_A, GUITARNOTE_B}; // Guitar equivalents

void launchpad::setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(playButton, INPUT);
  pinMode(bGuitarButton, INPUT);
  pinMode(SPEAKER, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(noteButtons[i], INPUT);
  }

  Wire.begin(SDA, SCL);
  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(3);
  lcd.clear();
  //lcd.print("Press PLAY");
}

void launchpad::loop() {
  if (digitalRead(playButton) == HIGH) {
    startGame();
  } else {
    idleMode(); // Just a playable keyboard now
  }
}

void idleMode() {
  for (int i = 0; i < 7; i++) {
    if (digitalRead(noteButtons[i]) == HIGH) {
      if (digitalRead(bGuitarButton) == LOW) {
        tone(SPEAKER, guitarNotes[i], 500);
      } else {
        tone(SPEAKER, pianoNotes[i], 500);
      }
      noTone(SPEAKER);
    }
    if (!once) {
      lcd.clear();
      lcd.print("Play Any Note");
      once = true;
    }
  }
}

bool waitForInput(int correctNote) {
  while (true) {
    for (int i = 0; i < 7; i++) {
      if (digitalRead(noteButtons[i]) == HIGH) {
          tone(SPEAKER, pianoNotes[i], 500);
          noTone(SPEAKER);
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

void startGame() {
  once = false;
  lcd.clear();
  lcd.print("Tune Box Game");
  delay(1000);

  for (int i=0; i<3; i++){
    lcd.clear();
    char notes[8] = "CDEFGAB";
    int sequence[3] = {random(7), random(7), random(7)};
    lcd.print("Play: ");
    for (int i=0; i<3; i++){
      lcd.print(notes[sequence[i]]);
    }
    delay(1000);
    for (int i=0; i<3; i++){
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