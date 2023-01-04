void speed_adjust() {
  int cl = 0;
  int list = 25;
  int tmpl = spl, tmpr = spr;
  while (1) {
    if (cl != spl) {
      cl = spl;
      display.clearDisplay();
      String value = String(cl, 10);
      text("LEFT :", 12, 16);
      text(value, 94, 16);
      display.drawRect(4, 41, 122, 13, WHITE);
      for (int i = 5; i <= (cl - 1) * 5 + 5; i++)
        for (int j = 42; j <= 52 ; j++) {
          display.drawLine(4, j, i, j, WHITE);
        }
      display.display();
    }
    if (digitalRead(ub) == LOW && spl < list) spl++;
    else if (digitalRead(db) == LOW && spl > 1) spl--;
    else if (digitalRead(mb) == LOW) {
      int t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          spl = tmpl;
          return;
        }
      }
      digitalWrite(13, LOW);
      EEPROM.write(7, spl);
      break;
    }
  }
  delay(100);
  cl = 0;
  //...............................................................................................right motor speed
  while (1) {
    if (cl != spr) {
      cl = spr;
      display.clearDisplay();
      String value = String(cl, 10);
      text("RIGHT :", 7, 16);
      text(value, 94, 16);
      display.drawRect(4, 41, 122, 13, WHITE);
      for (int i = 5; i <= (cl - 1) * 5 + 5; i++)
        for (int j = 42; j <= 52 ; j++) {
          display.drawLine(4, j, i, j, WHITE);
        }
      display.display();
    }
    if (digitalRead(ub) == LOW && spr < list) spr++;
    else if (digitalRead(db) == LOW && spr > 1) spr--;
    else if (digitalRead(mb) == LOW) {
      int t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          spr = tmpr;
          return;
        }
      }
      digitalWrite(13, LOW);
      EEPROM.write(8, spr);
      break;
    }
  }
  display.clearDisplay();
  text("DONE!!!", 23, 24);
  display.display();
}













//...........................................................................
void adjust() {
  int cl = 0;
  int list = 9;
  int flag = 0;
  int tempmenu = 1;
  while (1) {
    if (cl != tempmenu) {
      cl = tempmenu;
      if (cl == 1) {
        display.clearDisplay();
        text("END LINE", 17, 2);
        text("DELAY", 35, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 2) {
        display.clearDisplay();
        text("BRAKE", 35, 2);
        text("DIVIDER", 23, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 3) {
        display.clearDisplay();
        text("LOWEST", 29, 2);
        text("BRAKE", 35, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 4) {
        display.clearDisplay();
        text("HIGHEST", 23, 2);
        text("BRAKE", 35, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 5) {
        display.clearDisplay();
        text("  OBJECT  ", 04, 2);
        text(" BOUNDARY ", 04, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 6) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text(" BOUNDARY ", 04, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 7) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text(" MIDPOINT ", 04, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 8) {
        display.clearDisplay();
        text("   WALL   ", 04, 2);
        text("PROPORTION", 04, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
      else if (cl == 9) {
        display.clearDisplay();
        text("CALLIBRATE", 04, 2);
        text("PROPORTION", 04, 24);
        int q = EEPROM.read(cl + 8);
        String value = String(q, 10);
        if (q < 10) text(value, 59, 46);
        else if ( q < 100) text(value, 53, 46);
        else text(value, 47, 46);
        display.display();
      }
    }
    if (digitalRead(ub) == LOW && tempmenu < list) tempmenu++;
    else if (digitalRead(db) == LOW && tempmenu > 1) tempmenu--;
    else if (digitalRead(mb) == LOW) {
      int t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          display.clearDisplay();
          text("BYE!!!", 29, 24);
          display.display();
          mtd = EEPROM.read(9);
          d = EEPROM.read(10);
          base = EEPROM.read(11) * d;
          peak = EEPROM.read(12) * d;
          cl = base;
          brake = cl / d;
          object_boundary = EEPROM.read(13);
          wall_boundary = EEPROM.read(14);
          midpoint = EEPROM.read(15);
          wallp = EEPROM.read(16);
          cal_p = EEPROM.read(17) * 0.1;
          return;
        }
      }
      digitalWrite(13, LOW);
      adjustment_loop(cl, list);
      cl = 0;
    }
  }
}

void adjustment_loop(int a, int b) {
  int cl = -1;
  int list = 1200;
  int flag = 0;
  int temp[b + 1];
  int val[b + 1];
  for (int i = 1; i <= b; i++) temp[i] = val[i] = EEPROM.read(i + 8);

  while (1) {
    if (cl != val[a]) {
      cl = val[a];
      display.clearDisplay();
      String value = String(val[a], 10);
      text("ADJUST:", 5, 24);
      text(value, 90, 24);
      display.display();
    }
    if (digitalRead(ub) == LOW && val[a] < list) (a == 2 || a >= 5) ? val[a]++ : val[a] += 10;
    else if (digitalRead(db) == LOW && val[a] > 0) (a == 2 || a >= 5) ? val[a]-- : val[a] -= 10;
    else if (digitalRead(mb) == LOW) {
      int t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          display.clearDisplay();
          text("BYE!!!", 29, 24);
          display.display();
          val[a] = temp[a];
          return;
        }
      }
      digitalWrite(13, LOW);
      EEPROM.write(a + 8, val[a]);
      delay(10);
      display.clearDisplay();
      text("DONE!!!", 23, 24);
      display.display();
      return;
    }
  }
}
