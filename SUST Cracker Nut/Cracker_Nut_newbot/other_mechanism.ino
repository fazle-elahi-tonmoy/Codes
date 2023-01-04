void other_adjust() {
a:
  int list = 6;
  int p = 0;
  int q = 0;
  int temp = 0;
  while (digitalRead(swr) == HIGH) {
    delay(1);
    p = map(analogRead(13), 0, 1000, 1, list);
    if (temp != p) {
      temp = p;
      if (temp == 1) {
        display.clearDisplay();
        text("   SIDE   ", 04, 2);
        text("SELECTION", 10, 24);
        q = EEPROM.read(temp + 19);
        if (q == 0) text(" STRAIGHT ", 4, 46);
        else if (q == 2) text("LEFT HAND", 10, 46);
        else if (q == 1) text("RIGHT HAND", 4, 46);
        display.display();
      }
      else if (temp == 2) {
        display.clearDisplay();
        text("  OBJECT  ", 04, 2);
        text(" BOUNDARY ", 04, 24);
        q = EEPROM.read(temp + 19);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 3) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text(" BOUNDARY ", 04, 24);
        q = EEPROM.read(temp + 19);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 4) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text(" MIDPOINT ", 04, 24);
        q = EEPROM.read(temp + 19);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 5) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text("PROPORTION", 04, 24);
        q = EEPROM.read(temp + 19);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 6) {
        display.clearDisplay();
        text("CALLIBRATE", 04, 2);
        text("PROPORTION", 04, 24);
        q = EEPROM.read(temp + 19);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
    }
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 23, 24);
      display.display();
      delay(300);
      return;
    }
  }

  while (digitalRead(swr) == LOW) {
    delay(1);
  }

  while (1) {
    if (temp == 1) p = map(analogRead(13), 0, 1000, 0, 2);
    else if (temp >= 2 && temp <= 4) p = map(analogRead(13), 0, 1000, 0, 30);
    else if (temp == 5) p = map(analogRead(13), 0, 1000, 1, 10);
    else if (temp == 6) p = map(analogRead(13), 0, 1000, 1, 9);
    display.clearDisplay();
    String value = String(p, 10);
    text("ADJUST:", 5, 24);
    text(value, 90, 24);
    display.display();
    if (digitalRead(swl) == LOW) {
      display.clearDisplay();
      text("BYE!!!", 29, 24);
      display.display();
      delay(300);
      goto a;
    }
    if (digitalRead(swr) == LOW) {
      delay(100);
      while (digitalRead(swr) == LOW);
      display.clearDisplay();
      text("OKAY!!!", 29, 24);
      display.display();
      delay(300);
      EEPROM.write(temp + 19, p);
      delay(10);
      side = EEPROM.read(20);
      object_boundary = EEPROM.read(21);
      wall_boundary = EEPROM.read(22);
      midpoint = EEPROM.read(23);
      wallp = EEPROM.read(24);
      cal_p = EEPROM.read(25) * 0.1;
      goto a;
    }
  }
}

void headlight() {
  int cl = 0;
  while (digitalRead(swr) == HIGH && digitalRead(swl) == HIGH) {
    int p = map(analogRead(13), 0, 600, 1, 2);
    if (p == 2) {
      digitalWrite(light, 1);
      display.clearDisplay();
      text("    ON    " , 4, 24);
      display.display();
    }
    else if (p == 1) {
      digitalWrite(light, 0);
      display.clearDisplay();
      text("   OFF   " , 10, 24);
      display.display();
    }
  }
}
