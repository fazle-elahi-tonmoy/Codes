void braking_adjust() {
a:
  int list = 9;
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
        text("TURN", 41, 2);
        text("DELAY", 35, 24);
        q = EEPROM.read(temp + 10) * 5;
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 2) {
        display.clearDisplay();
        text("END LINE", 17, 2);
        text("DELAY", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 3) {
        display.clearDisplay();
        text(" INVERSE ", 10, 2);
        text("TIMER", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 4) {
        display.clearDisplay();
        text("   LOOP   ", 4, 2);
        text("DELAY", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 5) {
        display.clearDisplay();
        text("   TURN   ", 04, 2);
        text("SPEED", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 6) {
        display.clearDisplay();
        text("   TURN   ", 04, 2);
        text("BRAKE", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 7) {
        display.clearDisplay();
        text("BRAKE", 35, 2);
        text("DIVIDER", 23, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 8) {
        display.clearDisplay();
        text("LOWEST", 29, 2);
        text("BRAKE", 35, 24);
        q = EEPROM.read(temp + 10);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (temp == 9) {
        display.clearDisplay();
        text("HIGHEST", 23, 2);
        text("BRAKE", 35, 24);
        q = EEPROM.read(temp + 10);
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
    if (temp == 1) p = map(analogRead(13), 0, 1000, 250, 400);
    else if (temp == 2) p = map(analogRead(13), 0, 1000, 50, 250);
    else if (temp == 3) p = map(analogRead(13), 0, 1000, 0, 250);
    else if (temp == 4) p = map(analogRead(13), 0, 1000, 0, 150);
    else if (temp == 5) p = map(analogRead(13), 0, 1000, 150, 250);
    else if (temp == 6) p = map(analogRead(13), 0, 1000, 0, 150);
    else if (temp == 7) p = map(analogRead(13), 0, 1000, 1, 9);
    else if (temp == 8) p = map(analogRead(13), 0, 1000, 0, 250);
    else if (temp == 9) p = map(analogRead(13), 0, 1000, 0, 250);
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
      (temp == 1) ? EEPROM.write(temp + 10, p / 5) : EEPROM.write(temp + 10, p);
      delay(10);
      turn = EEPROM.read(11) * 5;
      mtd = EEPROM.read(12);
      rtd = EEPROM.read(13);
      ltd = EEPROM.read(14);
      tsp = EEPROM.read(15);
      br = EEPROM.read(16);
      d = EEPROM.read(17);
      base = EEPROM.read(18) * d;
      peak = EEPROM.read(19) * d;
      cl = base;
      brake = cl / d;
      goto a;
    }
  }
}
