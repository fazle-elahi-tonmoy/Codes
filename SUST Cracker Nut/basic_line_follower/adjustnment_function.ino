void counter_adjust() {
  int p;
  while (digitalRead(switchin) == HIGH) {
    p = map(analogRead(13), 0, 1020, 0, 9);
    display.clearDisplay();
    String value = String(p, 10);
    text("COUNTER:", 10, 24);
    text(value, 110, 24);
    display.display();
    if (digitalRead(calin) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  while (digitalRead(switchin) == LOW);

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
  while (digitalRead(switchin) == HIGH) {
    p = map(analogRead(13), 0, 1020, 0, 25);
    display.clearDisplay();
    String value = String(p, 10);
    text("LEFT :", 12, 16);
    text(value, 94, 16);
    display.drawRect(3, 41, 123, 13, WHITE);
    for (int i = 4; i <= p * 5 ; i++)
      for (int j = 42; j <= 52 ; j++) {
        display.drawLine(4, j, i, j, WHITE);
      }
    display.display();
    if (digitalRead(calin) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  EEPROM.write(6, p);
  delay(10);
  spl = EEPROM.read(6);

  while (digitalRead(switchin) == LOW);

  while (digitalRead(switchin) == HIGH) {
    p = map(analogRead(13), 0, 1020, 0, 25);
    display.clearDisplay();
    String value = String(p, 10);
    text("RIGHT :", 7, 16);
    text(value, 94, 16);
    display.drawRect(3, 41, 123, 13, WHITE);
    for (int i = 4; i <= p * 5; i++)
      for (int j = 42; j <= 52 ; j++) {
        display.drawLine(4, j, i, j, WHITE);
      }
    display.display();
    if (digitalRead(calin) == LOW) {
      display.clearDisplay();
      text("OKAY!!!", 23, 24);
      display.display();
      delay(300);
      return;
    }
  }

  while (digitalRead(switchin) == LOW);

  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
  delay(300);
  EEPROM.write(7, p);
  delay(10);
  spr = EEPROM.read(7);
}



void servo_adjust() {
  while (digitalRead(switchin) == HIGH) {
    gpos = map(analogRead(13), 0, 1020, 65, 140);
    grab.write(gpos);
    display.clearDisplay();
    text("GRAB:", 17, 24);
    String value = String(gpos, 10);
    text(value, 75, 24);
    display.display();
    if (digitalRead(calin) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 23, 24);
      display.display();
      delay(300);
      return;
    }
  }

  EEPROM.write(9, gpos);
  delay(10);

  while (digitalRead(switchin) == LOW) ;

  while (digitalRead(switchin) == HIGH) {
    hpos = map(analogRead(13), 0, 1020, 10, 100);
    handle.write(hpos);
    display.clearDisplay();
    text("HANDLE:", 5, 24);
    String value = String(hpos, 10);
    text(value, 87, 24);
    display.display();
    if (digitalRead(calin) == LOW) {
      display.clearDisplay();
      text("OKAY!!!", 29, 24);
      display.display();
      delay(300);
      return;
    }
  }
  EEPROM.write(8, hpos);
  delay(10);

  while (digitalRead(switchin) == LOW);

  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
  delay(300);
}
