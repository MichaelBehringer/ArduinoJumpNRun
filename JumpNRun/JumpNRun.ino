/*
 * Informatik Projekt von Harun Sebastian und Michael
 * Jump and Run auf dem LCD Display des Arduino
 * Verkabelung LCD: https://www.instructables.com/Arduino-Interfacing-With-LCD-Without-Potentiometer/
 * Github: https://github.com/MichaelBehringer/ArduinoJumpNRun
 */

#include <LiquidCrystal.h>
#include <IRremote.h> //Sketch->Bibliothek einbinden
#include <IRremoteInt.h> 

#include "pitches.h"
#include "jingles.h"
#include "constants.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

IRrecv irrecv(10);
decode_results results;

int Contrast=140;

int pos = 0;
int charPos = 0;
int tasterPin = 7;
int level = 0;
char buffer [10];

int readIrValue(){
  results.value = 0;
  irrecv.decode(&results);
  irrecv.resume();
  return results.value;
}

boolean isActionPressed(){
  return (digitalRead(tasterPin)==HIGH) || (readIrValue() != 0) ? true : false;
}

void waitTillButton(){
  while(true){
    if(isActionPressed()){
      return;
    }
  }
}

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
        
    if(isActionPressed()) { //fast exit bootingAnimation
      break;
    }
  }
  delay(500);
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

  while(true) {                              // Levelauswahl mit Pfeil
    for(int i = 0; i<4; i++) {
      lcd.setCursor(off[i][0], off[i][1]);
      lcd.write((byte) 0); // ""
      lcd.setCursor(on[i][0], on[i][1]);
      lcd.write((byte) 1); // pfeil
      for(int j = 0; j<5; j++){
        delay(200);
        if(isActionPressed()) {
          level = i+1;
          goto A; // (╯°□°）╯︵ ┻━┻ 
        }
      }
    }
  }
  A:;
}

void renderLine(int heightPos, int arr[]) {
   lcd.setCursor(0, heightPos);
   for(int i = 1; i<=15; i++) {
    lcd.write((byte) arr[i+pos]);
  }
}

void render(){
  lcd.clear();

  renderLine(0, top); 
  renderLine(1, bottom); 

  charPos = isActionPressed() ? 0 : 1; //set Char pos
  lcd.setCursor(0, charPos);
  lcd.write((byte) 5);
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

  failMusic();
  waitTillButton();
  pos=0;
}

void winScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("GEWONNEN");
  lcd.setCursor(0, 1);
  lcd.write("Punkte: OVER9000");
  winMusic();
  waitTillButton();
  pos=0;
}

void setup() {
   Serial.begin(9600);
   analogWrite(6, Contrast);
   lcd.begin(16, 2);
   irrecv.enableIRIn();
   
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
