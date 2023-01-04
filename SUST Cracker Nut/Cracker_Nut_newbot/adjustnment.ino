void counter_adjust() {
  int p;
  while (digitalRead(swr) == HIGH) {
    p = map(analogRead(13), 0, 1000, 0, 9);
    display.clearDisplay();
    String value = String(p, 10);
    text("COUNTER:", 10, 24);
    text(value, 110, 24);
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  while (digitalRead(swr) == LOW);

  EEPROM.write(10, p);
  delay(10);
  counter = EEPROM.read(10);

  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
  delay(300);
  return;
}


void speed_adjust() {
  int p;
  while (digitalRead(swr) == HIGH) {
    p = map(analogRead(13), 0, 1000, 0, 25);
    display.clearDisplay();
    String value = String(p, 10);
    text("SPEED:", 7, 16);
    text(value, 80, 16);
    display.drawRect(4, 41, 122, 13, WHITE);
    for (int i = 5; i <= (p - 1) * 5 + 5; i++)
      for (int j = 42; j <= 52 ; j++) {
        display.drawLine(4, j, i, j, WHITE);
      }
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  EEPROM.write(6, p);
  delay(10);
  sp = EEPROM.read(6);

  while (digitalRead(swr) == LOW);

  while (digitalRead(swr) == HIGH) {
    p = map(analogRead(13), 0, 1020, -127, 127);
    display.clearDisplay();
    String value = String(p, 10);
    text("ERROR:", 0, 16);
    text(value, 70, 16);
    display.drawRect(0, 41, 128, 13, WHITE);
    if (p > 0) {
      for (int i = 64; i <= (p / 2) + 64; i++)
        for (int j = 42; j <= 52 ; j++) {
          display.drawLine(64, j, i, j, WHITE);
        }
    }
    else if (p < 0) {
      for (int i = 64; i >= (p / 2) + 64; i--)
        for (int j = 42; j <= 52 ; j++) {
          display.drawLine(64, j, i, j, WHITE);
        }
    }
    else display.drawLine(64, 42, 64, 52, WHITE);
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("OKAY!!!", 23, 24);
      display.display();
      delay(300);
      return;
    }
  }

  while (digitalRead(swr) == LOW);

  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
  delay(300);
  EEPROM.write(7, p + 128);
  delay(10);
  spe = EEPROM.read(7)-128;
}



void servo_adjust() {
  while (digitalRead(swr) == HIGH) {
    gpos = map(analogRead(13), 0, 1020, 65, 140);
    grab.write(gpos);
    display.clearDisplay();
    text("GRAB:", 17, 24);
    String value = String(gpos, 10);
    text(value, 75, 24);
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 23, 24);
      display.display();
      delay(300);
      return;
    }
  }

  EEPROM.write(9, gpos);
  delay(10);

  while (digitalRead(swr) == LOW) ;

  while (digitalRead(swr) == HIGH) {
    hpos = map(analogRead(13), 0, 1020, 10, 100);
    handle.write(hpos);
    display.clearDisplay();
    text("HANDLE:", 5, 24);
    String value = String(hpos, 10);
    text(value, 87, 24);
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("OKAY!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  EEPROM.write(8, hpos);
  delay(10);

  while (digitalRead(swr) == LOW);

  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
  delay(300);
}
