short int getclickup() {
  short int t = 0, cl = 0;
  short int list = 5;
  if (digitalRead(ub) == LOW) {
    digitalWrite(13, HIGH);
    while (digitalRead(ub) == LOW) {
      t++;
      delay(1);
    }
  }
  digitalWrite(13, LOW);
  while (t > 15) {
    if (cl != upmenu) {
      cl = upmenu;
      if (cl == 1) text_line_follow();
      else if (cl == 2) {
        display.clearDisplay();
        text("CALLIBRATE", 5, 24);
        display.display();
      }
      else if (cl == 3) {
        display.clearDisplay();
        text("MOVE", 41, 16);
        text("STRAIGHT", 17, 42);
        display.display();
      }
      else if (cl == 4) {
        display.clearDisplay();
        text("BLUETOOTH", 11, 16);
        text("CONTROL", 23, 42);
        display.display();
      }
      else if(cl == 5){
        display.clearDisplay();
        text("HEADLIGHT", 11, 22);
        display.display();
      }
    }
    if (digitalRead(ub) == LOW && upmenu < list) upmenu++;
    else if (digitalRead(db) == LOW && upmenu > 1) upmenu--;
    else if (digitalRead(mb) == LOW) {
      t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          return list + 1;
        }
      }
      digitalWrite(13, LOW);
      return cl;
    }
  }
  return cl;
}


short int getclickdown() {
  short int t = 0, cl = 0;
  short int list = 5;
  if (digitalRead(db) == LOW) {
    digitalWrite(13, HIGH);
    while (digitalRead(db) == LOW) {
      t++;
      delay(1);
    }
  }
  digitalWrite(13, LOW);
  while (t > 15) {
    if (cl != downmenu) {
      cl = downmenu;
      if (cl == 1) {
        display.clearDisplay();
        text("ANALOG", 29, 16);
        text("READ", 41, 42);
        display.display();
      }
      else if (cl == 2) {
        display.clearDisplay();
        text("DIGITAL", 23, 16);
        text("READ", 41, 42);
        display.display();
      }
      else if (cl == 3) {
        display.clearDisplay();
        text("SONAR READ", 5, 24);
        display.display();
      }
      else if(cl == 4) text_speed_adjust();
      else if (cl == 5) {
        display.clearDisplay();
        text("ADJUSTMENT", 04, 16);
        text(" FUNCTION ", 04, 42);
        display.display();
      }
    }
    if (digitalRead(ub) == LOW && downmenu < list) downmenu++;
    else if (digitalRead(db) == LOW && downmenu > 1) downmenu--;
    else if (digitalRead(mb) == LOW) {
      t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          return list + 1;
        }
      }
      digitalWrite(13, LOW);
      return cl;
    }
  }
  return cl;
}

void getclickmid() {
  short int t = 0, cl = -1, limit = 20;
  short int temp = counter;
  if (digitalRead(mb) == LOW) {
    digitalWrite(13, HIGH);
    while (digitalRead(mb) == LOW) {
      t++;
      delay(1);
    }
  }
  digitalWrite(13, LOW);
  while (t > 15) {
    if (cl != counter) {
      cl = counter;
      display.clearDisplay();
      value = String(cl, 10);
      text("COUNTER:", 4, 24);
      text(value, 100, 24);
      display.display();
    }
    if (digitalRead(ub) == LOW && counter < limit) counter++;
    else if (digitalRead(db) == LOW && counter > 0) counter--;
    else if (digitalRead(mb) == LOW) {
      t = 0;
      digitalWrite(13, HIGH);
      while (digitalRead(mb) == LOW) {
        t++;
        delay(1);
        if (t >= 500) {
          digitalWrite(13, LOW);
          digitalWrite(7, HIGH);
          while (digitalRead(mb) == LOW);
          digitalWrite(7, LOW);
          counter = temp;
          sust_triplicata();
          return;
        }
      }
      digitalWrite(13, LOW);
      EEPROM.write(6, counter);
      display.clearDisplay();
      text("DONE!!!", 23, 24);
      display.display();
      sust_triplicata();
      return;
    }
  }
}
