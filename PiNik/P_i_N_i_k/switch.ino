byte getclickup() {
  byte t = 0, cl = 0, flag = 0;
  byte list = 5;
  if (digitalRead(ub) == LOW) {
    while (digitalRead(ub) == LOW) {
      t++;
      delay(1);
    }
  }
  while (t > 15) {
    if (cl != upmenu) {
      cl = upmenu;
      display.clearDisplay();
      if (cl == 1) text_line_follow();
      else if (cl == 2) text_maze_follow();
      else if (cl == 3) {
        text("   PATH   ", 4, 12);
        text(" DISPLAY ", 10, 38);
      }
      else if (cl == 4) {
        text("   MOVE   ", 04, 12);
        text(" STRAIGHT ", 04, 38);
      }

      else if (cl == 5) {
        text("  SIDE?  ", 10, 12);
        if (side == 0) text(" STRAIGHT ", 4, 38);
        else (side == 2) ? text("LEFT HAND", 10, 38) : text("RIGHT HAND", 4, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && upmenu < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); upmenu++;
    }
    else if (digitalRead(db) == LOW && upmenu > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); upmenu--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) return list + 1;
      else return cl;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
  return cl;
}


byte getclickdown() {
  byte t = 0, cl = 0, flag = 0;
  byte list = 5;
  if (digitalRead(db) == LOW) {
    while (digitalRead(db) == LOW) {
      t++;
      delay(1);
    }
  }
  while (t > 15) {
    if (cl != downmenu) {
      cl = downmenu;
      display.clearDisplay();
      if (cl == 1) text("  SENSOR  ", 04, 25);
      else if (cl == 2) text_speed_adjust();
      else if (cl == 3) {
        text(" BRAKING ", 10, 12);
        text("  ADJUST  ", 04, 38);
      }
      else if (cl == 4) {
        text("  OTHER  ", 10, 12);
        text("  ADJUST  ", 04, 38);
      }
      else if (cl == 5) {
        text(" CONTROL ", 10, 12);
        text("  SYSTEM  ", 4, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && downmenu < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); downmenu++;
    }
    else if (digitalRead(db) == LOW && downmenu > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); downmenu--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) return list + 1;
      else return cl;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
  return cl;
}

void getclickmid() {
  byte t = 0;
  if (digitalRead(mb) == LOW)
    while (digitalRead(mb) == LOW) {
      t++; delay(1);
    }
  if (t > 15) {
    counter = EEPROM.read(6);
    byte cl = counter + 1, flag = 0;
    while (t > 15) {
c:    if (cl != counter) {
        cl = counter;
        display.clearDisplay();
        value = String(cl, 10);
        text("COUNTER:" + value, 04, 25);
        display.display();
      }
      if (digitalRead(ub) == LOW && counter < 99) {
        (side_press(flag) == 1) ? flag = 1 : flag = 0;
        m81 = millis(); counter ++;
      }
      else if (digitalRead(db) == LOW && counter > 0) {
        (side_press(flag) == 1) ? flag = 1 : flag = 0;
        m81 = millis(); counter--;
      }
      else if (digitalRead(mb) == LOW) {
        if (long_press(1) == 0) EEPROM.write(6, counter); delay(10);
        pinik(); return;
      }
      m82 = millis();
      if (m82 - m81 > 25) flag = 0;
    }
  }
}

byte long_press(byte a) {
  short int p = 0;
  delay(50);
  display.setTextSize(2);
  while (digitalRead(mb) == LOW) {
    p++;
    delay(1);
    if (p >= 500) {
      digitalWrite(buzzer, HIGH);
      display.clearDisplay();-
      text("  BYE!!!  ", 04, 25);
      display.display();
      while (digitalRead(mb) == LOW);
      digitalWrite(buzzer, LOW);
      return 1;
    }
  }
  display.clearDisplay();
  if (a == 1) {
    text(" OKAY!!! ", 04, 25);
    display.display();
    beeping(2);
  }
  return 0;
}



byte side_press(byte a) {
  short int p = 0;
  while (digitalRead(ub) == LOW || digitalRead(db) == LOW) {
    p++; delay(1);
    if (digitalRead(ub) == LOW && digitalRead(db) == LOW) break;
    if (p >= 500 || a == 1) return 1;
  }
  return 0;
}
