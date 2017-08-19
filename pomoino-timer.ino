#include "LiquidCrystal.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int Buzzer = 10;
const int LeftBtn = 9;
const int RightBtn = 8;
int LeftBtnState = 0;
int RightBtnState = 0;

int ptime = 0;
char ftime[6];

const int pomodoroDuration = 25 * 60;
const int shortBreak = 5 * 60;
const int longBreak = 20 * 60;
const int longBreakInterval = 4;

typedef enum {STOPPED, WORKING, BREAK} StateType;
StateType curState = STOPPED;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Pomodoros: 0");

  
  pinMode(Buzzer, OUTPUT);
  pinMode(LeftBtn, INPUT);
  pinMode(RightBtn, INPUT);

}

void loop() {

  delay(1000);

  LeftBtnState = digitalRead(LeftBtn);
  RightBtnState = digitalRead(RightBtn);

  if (curState == STOPPED) {
    if (LeftBtnState) {
      curState = WORKING;
    }
  } else if (curState == WORKING) {
    if (RightBtnState) {
      curState = STOPPED;
      ptime = 0;
    } else {
      ptime++;
    }
  }


  sprintf(ftime, "%02d:%02d", ptime/60, ptime%60);
  lcd.setCursor(0,1);
  lcd.print(ftime);
//  noTone(Buzzer);
}
