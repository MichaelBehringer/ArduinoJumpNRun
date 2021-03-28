/*
 * Informatik Projekt von Harun Sebastian und Michael
 * Jump and Run auf dem LCD Display des Arduino
 * Verkabelung LCD: https://www.instructables.com/Arduino-Interfacing-With-LCD-Without-Potentiometer/
 */


#include <LiquidCrystal.h>
#include "pitches.h"
#include "constants.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Contrast=140;

int pos = 0;
int charPos = 0;
int tasterPin = 7;
int level = 0;
char buffer [10];


void bootingAnimation() {
  lcd.setCursor(0, 0);
  lcd.write("Info-Projekt von");
  char namen[65] = "                Harun, Sebastian und Michael               ";
  for(int i=0; i<45; i++){
    lcd.setCursor(0, 1);
    for(int j=0; j<=15; j++){
      lcd.write(namen[i+j]);
    }
    delay(500);
    
    if(digitalRead(tasterPin)==HIGH) { //emergency exit xd ^^
      break;
    }
  }
  delay(500);
}

void renderTop() {
  lcd.setCursor(0, 0);
  for(int i = 1; i<=15; i++) {
    lcd.write((byte) top[i+pos]);
  }
}

void renderBottom() {
  lcd.setCursor(0, 1);
  for(int i = 1; i<=15; i++) {
    lcd.write((byte) bottom[i+pos]);
  }
}

void render(){
  lcd.clear();
  
  renderTop();
  renderBottom();

  charPos = digitalRead(tasterPin)==HIGH ? 0 : 1;
  lcd.setCursor(0, charPos);
  lcd.write((byte) 5);
}

void waitTillButton(){
  while(true){
    if(digitalRead(tasterPin)==HIGH){
      return;
    }
  }
}

boolean checkColission(){
  return (top[pos]!=0 && charPos==0) || (bottom[pos]!=0 && charPos==1);
}

void failScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("GAME OVER");
  lcd.setCursor(0, 1);
  lcd.write("Punkte: ");
  itoa(pos,buffer,10);
  lcd.write(buffer);
  delay(1000);
  waitTillButton();
  pos=0;
}

void winScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("GEWONNEN");
  lcd.setCursor(0, 1);
  lcd.write("Punkte: OVER9000");
  delay(1000);
  waitTillButton();
  pos=0;
}

void menueScreen() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write("1-1");
  
  lcd.setCursor(10, 0);
  lcd.write("1-2");
  
  lcd.setCursor(1, 1);
  lcd.write("1-3");
  
  lcd.setCursor(10, 1);
  lcd.write("1-4");

  int off[][4] = {{9, 1}, {0, 0}, {9, 0}, {0, 1}};
  int on[][4] = {{0, 0}, {9, 0}, {0, 1}, {9, 1}};

  while(true) {
    for(int i = 0; i<4; i++) {
      lcd.setCursor(off[i][0], off[i][1]);
      lcd.write((byte) 0); // ""
      lcd.setCursor(on[i][0], on[i][1]);
      lcd.write((byte) 1); // pfeil
      for(int j = 0; j<5; j++){
        delay(200);
        if(digitalRead(tasterPin)==HIGH) {
          level = i+1;
          goto A; // (╯°□°）╯︵ ┻━┻ Michael Approved
        }
      }
    }
  }
  A:;
}

void levelStartMusic() { //TODO add real sound tee-hee ^^
  tone(8, NOTE_C5, 400);
  delay(200);
  tone(8, NOTE_D5, 400);
  delay(200);
  tone(8, NOTE_E5, 400);
  delay(200);
  tone(8, NOTE_G5, 400);
  delay(400);
  tone(8, NOTE_E5, 400);
  delay(200);
  tone(8, NOTE_G5, 400);
  delay(600);
}

void setup() {
   Serial.begin(9600);
   analogWrite(6, Contrast);
   lcd.begin(16, 2);
   
   lcd.createChar(0, nothing);
   lcd.createChar(1, arrow);
   lcd.createChar(2, block1);
   lcd.createChar(3, block2);
   lcd.createChar(4, craw);
   lcd.createChar(5, player);
   lcd.createChar(6, goalT);
   lcd.createChar(7, goalB);

  bootingAnimation();
}

void loop() {
  // put your main code here, to run repeatedly:
  menueScreen();
  levelStartMusic();

  while(true){
  render();
  pos++;

  if(checkColission()) {break;}
  
  delay(2000 / level);
  }

  if(top[pos]==6&&bottom[pos]==7){
    winScreen();
  } else {
    failScreen();
  }
}
