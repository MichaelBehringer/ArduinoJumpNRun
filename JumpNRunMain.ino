#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int Contrast=140;
int top[] = {0,0,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,0,1};
int bottom[] = {0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1};

int pos = 0;

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

void renderTop() {
  for(int i = 0; i<14; i++) {
    lcd.setCursor(i, 0);
    if(top[i+pos]!=0){
      //lcd.setCursor(i, 0);
      lcd.write((byte)1);
    } else {
      lcd.write((byte)2);
    }
    

      
    //printf("pos: %d, char: %d", i, top[i+pos])
  }
}

void render(){
  renderTop();
  //renderBottom();
}

void setup() {
   analogWrite(6,Contrast);
   lcd.begin(16, 2);
   lcd.createChar(1, block);
   
   lcd.createChar(2, nothing);
}

void loop() {
  // put your main code here, to run repeatedly:
  render();
  delay(1000);
  pos++;
  //lcd.setCursor(3, 0);
  //lcd.write((byte)1);
}
