String brake_show(byte a) {
  if (a == 1)  return "BRAKE DIVIDER---";
  else if (a == 2)  return "LOWEST BRAKE----";
  else if (a == 3)  return "HIGHEST BRAKE---";
  else if (a == 4)  return "TURN SPEED------";
  else if (a == 5)  return "TURN BRAKE------";
  else if (a == 6)  return "NODE DELAY------";
  else if (a == 7)  return "U TURN DELAY----";
  else if (a == 8)  return "ROTATION DELAY--";
  else if (a == 9)  return "REVERSE TIMER---";
  else if (a == 10) return "STOP TIMER------";
  else if (a == 11) return "BYPASS DELAY----";
  else if (a == 12) return "OVERTAKE DELAY--";
}

void braking() {
  byte cl = 0, b = 1, p = 5, flag = 0, list = 12, temp = 1;
  while (1) {
    if (cl != temp) {
      cl = temp;
      display.clearDisplay();
      display.setTextSize(1);
      int j = 0;
      for (byte i = b; i <= p; i++) {
        (i == cl) ? display.setTextColor(BLACK, WHITE) : display.setTextColor(WHITE);
        (i == 1 || i == 5 || i == 6) ? value = String(EEPROM.read(i + 10), 10) : value = String(EEPROM.read(i + 10) * 10, 10);
        text(brake_show(i) + " " + value, 2, j + 2); j += 12;
      }
      display.display();
    }
    if (digitalRead(mb) == LOW) {
      display.setTextColor(WHITE);
      if (long_press(0) == 1) {
        d = EEPROM.read(11);
        base = EEPROM.read(12) * d * 10;
        peak = EEPROM.read(13) * d * 10;
        tsp = EEPROM.read(14) * 10;
        br = EEPROM.read(15);
        ltd = EEPROM.read(16);
        mtd = EEPROM.read(17) * 10;
        rotation = EEPROM.read(18) * 10;
        rtd = EEPROM.read(19) * 10;
        stp_delay = EEPROM.read(20) * 10;
        o1 = EEPROM.read(21) * 10;
        o2 = EEPROM.read(22) * 10;
        cl = base;
        return;
      }
      else adjustment_loop1(cl);
      cl = 0;
    }
    else if (digitalRead(ub) == LOW && temp < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); temp++;
      if (temp > p) {
        p = temp; b = p - 4;
      }
    }
    else if (digitalRead(db) == LOW && temp > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); temp--;
      if (temp < b ) {
        b = temp; p = b + 4;
      }
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}

void adjustment_loop1(byte a) {
  byte flag = 0, func;
  (a == 1 || a == 5 || a == 6) ? func = 1 : func = 10;
  int cl = -1, list = 255 * func, val = EEPROM.read(a + 10) * func;

  while (1) {
    if (cl != val) {
      cl = val;
      display.clearDisplay();
      value = String(val, 10);
      text("VALUE:" + value, 04, 25);
      display.display();
    }
    if (digitalRead(ub) == LOW && val < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); val += func;
    }
    else if (digitalRead(db) == LOW && val > 0) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); val -= func;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(1) == 1) return;
      EEPROM.write(a + 10, val / func);
      delay(10); return;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}
