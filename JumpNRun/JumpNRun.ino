/*
 * Informatik Projekt von Aleyna Cikrik
 * Jump and Run auf dem LCD Display des Arduino
 * Verkabelung LCD: https://www.instructables.com/Arduino-Interfacing-With-LCD-Without-Potentiometer/
 */

#include <LiquidCrystal.h>

#include "pitches.h" //Töne
#include "jingles.h" //Melodien
#include "constants.h" //Konstanten

#define joyX A0 //Joy Stick
#define joyY A1

int height = 0; //Character höhe
int prevHeight = 0;

int Contrast=75; //LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int pos = 0;
int charPos = 0;
int tasterPin = 7;
int level = 0;
char buffer [10];

boolean isActionPressed(){ //ist Taster gedrückt
  return (digitalRead(tasterPin)==HIGH);
}

void waitTillButton(){ //unendlichschleife bis Taster gedrückt wird
  while(true){
    if(isActionPressed()){
      return;
    }
  }
}

void bootingAnimation() { //booting Animation mit coolem Text uwu
  lcd.setCursor(0, 0);
  lcd.write("AnPr-Projekt");
  char slider[65] = "                Aleyna Cikrik 03.12.2021 12A               ";
  for(int i=0; i<45; i++){
    lcd.setCursor(0, 1);
    for(int j=0; j<=15; j++){
      lcd.write(slider[i+j]);
    }
    delay(500);
        
    if(isActionPressed()) { //überspringen
      break;
    }
  }
  delay(500);
}

void menueScreen() { //Levelauswahl
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write("1-1");
  
  lcd.setCursor(10, 0);
  lcd.write("1-2");
  
  lcd.setCursor(1, 1);
  lcd.write("1-3");
  
  lcd.setCursor(10, 1);
  lcd.write("1-4");

  int off[][4] = {{9, 1}, {0, 0}, {9, 0}, {0, 1}}; //Positionen zum Pfeil löschen
  int on[][4] = {{0, 0}, {9, 0}, {0, 1}, {9, 1}}; //Positionen zum Pfeil malen

  while(true) { //Neuen Pfeil malen und alten Pfeil löschen
    for(int i = 0; i<4; i++) {
      lcd.setCursor(off[i][0], off[i][1]);
      lcd.write((byte) 0); // ""
      lcd.setCursor(on[i][0], on[i][1]);
      lcd.write((byte) 1); // pfeil
      for(int j = 0; j<15; j++){
        delay(100);
        if(isActionPressed()) { //Level ausgewählt
          level = i+1;
          goto A; // (╯°□°）╯︵ ┻━┻ 
        }
      }
    }
  }
  A:;
}

void renderLine(int heightPos, int arr[]) { //Zeile Malen
   lcd.setCursor(0, heightPos);
   for(int i = 1; i<=15; i++) {
    lcd.write((byte) arr[i+pos]);
  }
}

void render(){ //Aufruf der Render Funktionen + Charakter rendern
  lcd.clear();

  renderLine(0, top); //Zeile oben
  renderLine(1, bottom); //Zeile unten

  height = getCharHeight();
  if(prevHeight == 1 && height == 0) { //not perfect but works
      tone(8, 2700, 50);
  }
  lcd.setCursor(0, height);
  prevHeight = height;
  
  lcd.write((byte) 5); //Character
}

int getCharHeight(){ //Ist Character oben oder unten
  return isJoyTop() || isActionPressed() ? 0 : 1;
}

boolean checkColission(){ //check colissions
  return (top[pos+1]!=0 && getCharHeight()==0) || (bottom[pos+1]!=0 && getCharHeight()==1);
}

boolean isJoyTop(){
  return (analogRead(joyX) < 100);
}

boolean isJoyBottom(){
  return (analogRead(joyX) > 500);
}

boolean isJoyRight(){
  return (analogRead(joyY) < 100);
}

boolean isJoyLeft(){
  return (analogRead(joyY) > 500);
}

void failScreen() { //fail Screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("GAME OVER");
  lcd.setCursor(0, 1);
  lcd.write("Punkte: ");
  itoa(pos,buffer,10); //Wandelt integer zu Sting um
  lcd.write(buffer);

  failMusic();
  waitTillButton();
  pos=0;
}

void winScreen() { //win Screen
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
   analogWrite(6,Contrast);
   lcd.begin(16, 2);
   
   lcd.createChar(0, nothing); //Charaktermodelle dem LCD Display "beibringen" //in constants.h gespeichert
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
    if(isJoyRight()){
       pos++; //rechts
    }
    if(isJoyLeft() && pos > 0){
       pos--; //links
    }
    
    render();
    
    if(checkColission()) {
      break; //unendlichschleife beenden falls Treffer
    }
    
    delay(1500/level); //Geschwindigkeit gemäß Lebel
  }
  
  if(top[pos+1]==6&&bottom[pos+1]==7){ //Überprüfung ob Kollision mit Ziel oder mit Stein/Vogel
    winScreen();
  } else {
    failScreen();
  }
}
