#include "LiquidCrystal.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int Buzzer = 10;
const int LeftBtn = 9;
const int RightBtn = 8;
int LeftBtnState = 0;
int RightBtnState = 0;

int ptime = 0;

double a = millis();
double c; 

char ftime[6];
int pomodoroCount = 0;

const int pomodoroDuration = 25 * 60;
const int shortBreak = 5 * 60;
const int longBreak = 20 * 60;
const int longBreakInterval = 4;
int buzzerDuration = 0;

typedef enum {STOPPED, WORKING, BREAK} StateType;
StateType curState = STOPPED;


void printStatus() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pomodoros: ");
  lcd.print(pomodoroCount);
  sprintf(ftime, "%02d:%02d", (ptime)/60, (ptime )%60);
  lcd.setCursor(0,1);
  lcd.print(ftime);
}

void setup() {
  lcd.begin(16, 2);

  
  pinMode(Buzzer, OUTPUT);
  pinMode(LeftBtn, INPUT);
  pinMode(RightBtn, INPUT);
  printStatus();
}

void stopTimer() {
  curState = STOPPED;
  a = millis();
  ptime = 0;
}
void loop() {

  delay(100);

  if (buzzerDuration > 0) {
    buzzerDuration--;
  } else {
    noTone(Buzzer);
  }
  LeftBtnState = digitalRead(LeftBtn);
  RightBtnState = digitalRead(RightBtn);

  if (curState == STOPPED) {
    a = millis();
    if (LeftBtnState) {
      curState = WORKING;
    }

    if (RightBtnState) {
      pomodoroCount = 0;
    }
  } else if (curState == WORKING) {
    if (RightBtnState) {
      stopTimer();
    } else {
      c = millis();
      ptime = (c - a) / 1000;
    }

    if (ptime > pomodoroDuration) {
      stopTimer();
      pomodoroCount++;
      tone(Buzzer, 800);
      buzzerDuration = 10;
    }
  }
  printStatus();
}
