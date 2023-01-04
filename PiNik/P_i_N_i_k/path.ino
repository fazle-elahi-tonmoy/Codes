void counter_display(byte d, byte temp) {
  byte cl = 0, b = 1, p = 8, flag = 0;
  if (temp > p) {
    p = temp; b = p - 7;
  }
  while (1) {
c:    if (cl != temp) {
      cl = temp;
      (d == 0) ? display.invertDisplay(false) : display.invertDisplay(true);
      display.clearDisplay();
      display.setTextSize(1);
      int x = 0;
      for (byte i = b; i <= p; i++) {
        (i == cl) ? display.setTextColor(BLACK, WHITE) : display.setTextColor(WHITE);
        byte j = EEPROM.read((i - 1) + m_base);
        value = String(i, 10) + ". " + show(j);
        text(value, 0, x); x += 8;
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && digitalRead(db) == LOW && d == 0) {
      display.clearDisplay(); display.setTextSize(2); display.setTextColor(WHITE);
      text(" SPECIAL ", 10, 12);
      text(" FUNCTION ", 04, 38);
      display.display();
      while (digitalRead(ub) == LOW || digitalRead(db) == LOW);
      special_function(temp);
      cl = 0;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        return;
      }
      else {
        adjustment(cl, d);
        while (digitalRead(mb) == LOW);
        cl = 0;
      }
    }
    else if (digitalRead(ub) == LOW && temp < 100) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); temp++;
      if (temp > p) {
        p = temp; b = p - 7;
      }
    }
    else if (digitalRead(db) == LOW && temp > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); temp--;
      if (temp < b ) {
        b = temp; p = b + 7;
      }
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}

String show(byte a) {
  if (a == 0) return "EMPTY";
  else if (a == 1) return "RIGHT";
  else if (a == 2) return "STRAIGHT";
  else if (a == 3) return "LEFT";
  else if (a == 4) return "U TURN";
  else if (a == 5) return "T LEFT";
  else if (a == 6) return "T RIGHT";
  else if (a == 7) return "INVERSE";
  else if (a == 8) return "WALL";
  else if (a == 9) return "OBSTACLE";
  else if (a == 10) return "CHECKPOST";
  else if (a == 11) return "LINE GAP";
  else if (a == 12) return "CONTINUE";
  else if (a == 13) return "HEADLIGHT";
  else return "GARBAGE";
}

void adjustment(byte a, byte b) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  byte t = EEPROM.read((a - 1) + m_base), c = -1, list = 13;
  if (b == 2) {
    for (byte i = a + m_base; i < 100 + m_base; i++) {
      EEPROM.write(i - 1, EEPROM.read(i));
      delay(5);
    }
    EEPROM.write(99 + m_base, 0);
    delay(5);
  }
  else
    while (1) {
      if (c != t) {
        display.clearDisplay();
        c = t;
        if (t > list) t = list;
        value = show(t);
        text(value, 0, 26);
        display.display();
      }

      if (digitalRead(ub) == LOW && t < list) {
        delay(100); t++;
      }
      else if (digitalRead(db) == LOW && t > 0) {
        delay(100); t--;
      }
      else if (digitalRead(mb) == LOW) {
        if (long_press(1) == 1) return;
        else {
          if (b == 0) {
            EEPROM.write((a - 1) + m_base , t);
            delay(5);
          }
          else if (b == 1) {
            for (byte p = 100 + m_base; p >= (a - 1) + m_base; p--) {
              EEPROM.write(p, EEPROM.read(p - 1));
              delay(5);
            }
            EEPROM.write((a - 1) + m_base , t);
            delay(5);
          }
          return;
        }
      }
    }
}

void special_function(byte a) {
  byte cl = 0 , t = 1;
  while (1) {
    if (cl != t) {
      cl = t;
      display.clearDisplay();
      display.setTextSize(2);
      if (cl == 1) text("CLEAR ALL", 10, 26);
      else if (cl == 2) text(" ADD CELL ", 04, 26);
      else if (cl == 3) {
        text("  DELETE  ", 04, 12);
        text("   CELL   ", 04, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && t < 3) {
      delay(100); t++;
    }
    else if (digitalRead(db) == LOW && t > 1) {
      delay(100); t--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(1) == 1) return;
      if (cl == 1)
        for (byte i = 0; i < 100 ; i++) {
          if (EEPROM.read(i + m_base) != 0) {
            EEPROM.write(i + m_base, 0);
            delay(5);
          }
        }
      else counter_display(cl - 1, a);
      return;
    }

  }
}
