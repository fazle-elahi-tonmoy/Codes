void speed_adjust() {
  short int cl = -1;
  short int tmp = sp, tmpe = spe, flag = 0;
  while (1) {
    if (cl != sp) {
      cl = sp;
      display.clearDisplay();
      value = String(cl * 10, 10);
      text("SPEED:", 7, 16);
      text(value, 80, 16);
      display.drawRect(4, 41, 122, 13, WHITE);
      for (byte i = 5; i <= (cl - 1) * 5 + 5; i++)
        for (byte j = 42; j <= 52 ; j++) {
          display.drawLine(4, j, i, j, WHITE);
        }
      display.display();
    }
    if (digitalRead(ub) == LOW && sp < 25) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis(); sp++;
    }
    else if (digitalRead(db) == LOW && sp > 0) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis(); sp--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(1) == 1) {
        sp = tmp; return;
      }
      else EEPROM.write(7, sp);
      break;
    }
    m82 = millis();
    if (m82 - m81 > 25)flag = 0;
  }
  cl = 300;
  //...............................................................................................right motor speed
  while (1) {
    if (cl != spe) {
      cl = spe;
      display.clearDisplay();
      value = String(cl, 10);
      text("ERROR:", 0, 16);
      text(value, 70, 16);
      display.drawRect(0, 41, 128, 13, WHITE);
      if (spe > 0) {
        for (byte i = 64; i <= (spe / 2) + 64; i++)
          for (byte j = 42; j <= 52 ; j++) {
            display.drawLine(64, j, i, j, WHITE);
          }
      }
      else if (spe < 0) {
        for (byte i = 64; i >= (spe / 2) + 64; i--)
          for (byte j = 42; j <= 52 ; j++) {
            display.drawLine(64, j, i, j, WHITE);
          }
      }
      else display.drawLine(64, 42, 64, 52, WHITE);
      display.display();
    }
    if (digitalRead(ub) == LOW && spe < 127) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis(); spe++;
    }
    else if (digitalRead(db) == LOW && spe > -127) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis(); spe--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(1) == 1) {
        spe = tmpe; return;
      }
      else EEPROM.write(8, spe + 128);
      break;
    }
    m82 = millis();
    if (m82 - m81 > 25)flag = 0;
  }
}

//...........................................................................
String other_show(byte a) {
  if (a == 1)      return "OBJECT BOUNDARY--";
  else if (a == 2) return "WALL BOUNDARY----";
  else if (a == 3) return "WALL MIDPOINT----";
  else if (a == 4) return "WALL PROPORTION--";
  else if (a == 5) return "CAL PROPORTION---";
  else if (a == 6) return "LINE PROPORTION--";
  else if (a == 7) return "LINE BRAKE-------";
}

void other() {
  byte cl = 0, b = 1, p = 5, flag = 0, list = 7, temp = 1;
  while (1) {
    if (cl != temp) {
      cl = temp;
      display.clearDisplay();
      display.setTextSize(1);
      int j = 0;
      for (byte i = b; i <= p; i++) {
        (i == cl) ? display.setTextColor(BLACK, WHITE) : display.setTextColor(WHITE);
        (i == 6 || i == 5) ? value = String((float)EEPROM.read(i + 24) * 0.1, 1) : value = String(EEPROM.read(i + 24), 10);
        text(other_show(i) + " " + value, 2, j + 2); j += 12;
      }
      display.display();
    }
    if (digitalRead(mb) == LOW) {
      display.setTextColor(WHITE);
      if (long_press(0) == 1) {
        object_boundary = EEPROM.read(25);
        wall_boundary = EEPROM.read(26);
        midpoint = EEPROM.read(27);
        wallp = EEPROM.read(28);
        cal_p = EEPROM.read(29) * 0.1;
        line_p = EEPROM.read(30) * 0.1;
        line_d = EEPROM.read(31);
        return;
      }
      else adjustment_loop2(cl);
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

void adjustment_loop2(byte a) {
  byte cl = 255, list, val = EEPROM.read(a + 24), temp = val;
  byte flag = 0;
  if (a == 5 || a == 7) list = 10;
  else if (a == 4) list = 20;
  else if (a == 6) list = 47;
  else list = 250;

  while (1) {
    if (cl != val) {
      cl = val;
      display.clearDisplay();
      (a == 6 || a == 5) ? value = String((float)val * 0.1, 1) : value = String(val, DEC);
      text("VALUE:" + value, 04, 24);
      display.display();
    }
    if (digitalRead(ub) == LOW && val < list) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis();  val++;
    }
    else if (digitalRead(db) == LOW && val > 0) {
      if (side_press(flag) == 1) flag = 1;
      m81 = millis();  val--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(1) == 1) return;
      EEPROM.write(a + 24, val); delay(10);
      if (a == 5)
        for (byte i = 0; i < 6 ; i++) {
          trash[i] = trash[i] / temp;
          trash[i] = trash[i] * val;
          EEPROM.write(i, trash[i] / 5 ); delay(10);
        }
      return;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}
