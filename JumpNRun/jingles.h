/*************************************************

 * Custom Jingles

*************************************************/

void levelStartMusic() {
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

void failMusic() {
  tone(8, NOTE_G4, 400);
  delay(300);
  tone(8, NOTE_E4, 400);
  delay(300);
  tone(8, NOTE_D4, 400);
  delay(300);
  tone(8, NOTE_C4, 400);
  delay(800);
}

void winMusic() {
  tone(8, NOTE_E5, 400);
  delay(150);
  noTone(8);
  delay(50);
  tone(8, NOTE_E5, 400);
  delay(150);
  noTone(8);
  delay(50);
  tone(8, NOTE_E5, 400);
  delay(150);
  noTone(8);
  delay(50);
  tone(8, NOTE_E5, 600);
  delay(600);
  tone(8, NOTE_C5, 600);
  delay(600);
  tone(8, NOTE_E5, 400);
  delay(400);
  tone(8, NOTE_G5, 400);
  delay(400);
  tone(8, NOTE_E5, 400);
  delay(200);
  tone(8, NOTE_G5, 400);
  delay(400);
}
