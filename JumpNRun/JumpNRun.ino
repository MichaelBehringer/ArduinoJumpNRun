/*
 * Informatik Projekt von Harun Sebastian und Michael
 * Jump and Run auf dem LCD Display des Arduino
 * Verkabelung LCD: https://www.instructables.com/Arduino-Interfacing-With-LCD-Without-Potentiometer/
 */


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Contrast=140;
int top[] = {0,0,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,0,1};
int bottom[] = {0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1};

int pos = 0;
int charPos = 0;
int tasterPin = 7;
char buffer [10];

const byte nothing[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
const byte player[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
};
const byte block[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

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
  lcd.write((byte) 10);
}

void waitTillButton(){
  while(true){
    if(digitalRead(tasterPin)==HIGH){
      return;
    }
  }
}

void setup() {
   Serial.begin(9600);
   analogWrite(6, Contrast);
   lcd.begin(16, 2);
   
   lcd.createChar(0, nothing);
   lcd.createChar(1, block);
   lcd.createChar(10, player);
}

boolean checkColission(){
  return (top[pos]!=0 && charPos==0) || (bottom[pos]!=0 && charPos==1) ? true : false;
}

void loop() {
  // put your main code here, to run repeatedly:
  render();
  pos++;

  if(checkColission()){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.write("Punkte: ");
    itoa(pos,buffer,10);
    lcd.write(buffer);
    waitTillButton();
    pos=0;
  }

  delay(1000);
}
