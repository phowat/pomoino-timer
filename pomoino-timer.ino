#include "LiquidCrystal.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int Buzzer = 10;
const int LeftBtn = 9;
const int RightBtn = 8;
int LeftBtnState = 0;
int RightBtnState = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Pomodoros: 0");
  lcd.setCursor(0,1);
  lcd.print("00:00"); 
  
  pinMode(Buzzer, OUTPUT);
  pinMode(LeftBtn, INPUT);
  pinMode(RightBtn, INPUT);

}

void loop() {
  LeftBtnState = digitalRead(LeftBtn);
  if(LeftBtnState) {
    tone(Buzzer, 3000);  
  } else {
    noTone(Buzzer);
  }

  RightBtnState = digitalRead(RightBtn);
  if(RightBtnState) {
    lcd.setCursor(0,1);
    lcd.print("BUNDA");
  } else {
        lcd.setCursor(0,1);
    lcd.print("SUJA");
  }

//  noTone(Buzzer);
}
