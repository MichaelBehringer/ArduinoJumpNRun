/*
 * Informatik Projekt von Harun Sebastian und Michael
 * Jump and Run auf dem LCD Display des Arduino
 * Verkabelung LCD: https://www.instructables.com/Arduino-Interfacing-With-LCD-Without-Potentiometer/
 */


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Contrast=140;
int top[] =    {0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int bottom[] = {0,0,0,0,0,0,2,0,0,0,3,3,0,2,0,0,0,0,0,3,0,0,2,0,0,0,0,0,0,3,2,0,0,2,0,0,0,0,0,2,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int pos = 0;
int charPos = 0;
int tasterPin = 7;
char buffer [10];
int level = 0;

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
const byte arrow[8] = {
  B01000,
  B01100,
  B01110,
  B11111,
  B01110,
  B01100,
  B01000,
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
const byte block1[8] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
};
const byte block2[8] = {
  B11111,
  B11011,
  B10001,
  B10001,
  B10001,
  B10001,
  B11011,
  B11111,
};
const byte craw[8] = {
  B00110,
  B11111,
  B11111,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};
const byte goalT[8] = {
  B00010,
  B00110,
  B01110,
  B11110,
  B00110,
  B00110,
  B00110,
  B00110,
};
const byte goalB[8] = {
  B00110,
  B00110,
  B00110,
  B00110,
  B00110,
  B11111,
  B11111,
  B11111,
};
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
  }
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
  waitTillButton();
  pos=0;
}

void winScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("GEWONNEN");
  lcd.setCursor(0, 1);
  lcd.write("Punkte: OVER9000");
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


  while(true) {
    lcd.setCursor(9, 1);
    lcd.write((byte) 0); // ""
    lcd.setCursor(0, 0);
    lcd.write((byte) 1); // pfeil
    delay(1000);
    if(digitalRead(tasterPin)==HIGH) {
      level = 1;
      break;
    }
    
    lcd.setCursor(0, 0);
    lcd.write((byte) 0); // ""
    lcd.setCursor(9, 0);
    lcd.write((byte) 1); // pfeil
    delay(1000);
    if(digitalRead(tasterPin)==HIGH) {
      level = 2;
      break;
    }
    
    lcd.setCursor(9, 0);
    lcd.write((byte) 0); // ""
    lcd.setCursor(0, 1);
    lcd.write((byte) 1); // pfeil
    delay(1000);
    if(digitalRead(tasterPin)==HIGH) {
      level = 3;
      break;
    }
    
    lcd.setCursor(0, 1);
    lcd.write((byte) 0); // ""
    lcd.setCursor(9, 1);
    lcd.write((byte) 1); // pfeil -------------------- der code ist noch hässlich TOOOOOOOOOOODOOOO !!!!!!!!!!111elf //vll umweg mit array ka
    delay(1000);
    if(digitalRead(tasterPin)==HIGH) {
      level = 4;
      break;
    }
    
  }
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

  //bootingAnimation();
}

void loop() {
  // put your main code here, to run repeatedly:
  menueScreen();

  do{
  delay(2000 / level);
  render();
  pos++;

  } while(!checkColission());

  if(top[pos]==6&&bottom[pos]==7){
    winScreen();
  } else {
    failScreen();
  }
}
