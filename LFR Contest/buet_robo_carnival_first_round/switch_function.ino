int getclick1() {
  int t = 0, cl = 0;

  if (digitalRead(calin) == HIGH) {
check : while (digitalRead(calin) == HIGH) {
      delay(1);
      digitalWrite(calout, HIGH);
      t++;
    }
    digitalWrite(calout, LOW);
    if (t >= 15) cl++;
    if (cl == 1) {
      text_line_follow();
    }
    else if (cl == 2) {
      display.clearDisplay();
      text("ANALOG", 29, 16);
      text("READ", 41, 42);
      display.display();
    }
    else if (cl == 3) {
      display.clearDisplay();
      text("DIGITAL", 23, 16);
      text("READ", 41, 42);
      display.display();
    }
    else if (cl == 4) {
      display.clearDisplay();
      text("SONAR READ", 5, 24);
      display.display();
    }
    else if (cl == 5) {
      display.clearDisplay();
      text("CALLIBRATE", 5, 24);
      display.display();
    }
    else if (cl == 6) {
      display.clearDisplay();
      display.display();
      return cl;
    }
    t = 0;
    while (digitalRead(calin) == LOW) {
      t++;
      delay(1);
      if (t >= 1000) break;
    }
    if (t < 1000) goto check;
  }
  return cl;
}
//...................................................................................................






//..............................................................................................
int getclick2() {
  int t = 0, cl = 0;

  if (digitalRead(switchin) == HIGH) {
check : while (digitalRead(switchin) == HIGH) {
      delay(1);
      digitalWrite(calout, HIGH);
      t++;
    }
    digitalWrite(calout, LOW);
    if (t >= 15) cl++;
    if (cl == 1) {
      display.clearDisplay();
      text("Counter 0", 10, 24);
      display.display();
    }
    else if (cl == 2) {
      display.clearDisplay();
      text("Counter 1", 10, 24);
      display.display();
    }
    else if (cl == 3) {
      display.clearDisplay();
      text("Counter 2", 10, 24);
      display.display();
    }
    else if (cl == 4) {
      display.clearDisplay();
      text("Counter 4", 10, 24);
      display.display();
    } 
    else if (cl == 5) {
      display.clearDisplay();
      text("STRAIGHT", 17, 16);
      text("RUN", 47, 42);
      display.display();
    }
    else if (cl == 6) {
      display.clearDisplay();
      text("BATTERY", 23, 16);
      text("CHECK", 35, 42);
      display.display();
    }
    else if (cl == 7) {
      display.clearDisplay();
      display.display();
      return cl;
    }
    t = 0;
    while (digitalRead(switchin) == LOW) {
      t++;
      delay(1);
      if (t >= 1000) break;
    }
    if (t < 1000) goto check;
  }
  return cl;
}

