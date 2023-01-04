int menu_function1() {
  int list = 7;
  int p = 0;
  int temp = 0;
  if (digitalRead(swl) == LOW) {
    delay(100);
    while (digitalRead(swl) == LOW) {
      delay(1);
    }
    while (digitalRead(swl) == HIGH) {
      delay(1);
      p = map(analogRead(13), 0, 1000, 1, list);
      if (temp != p) {
        temp = p;
        if (temp == 1) text_line_follow();
        else if (temp == 2) {
          display.clearDisplay();
          text("CALLIBRATE", 5, 24);
          display.display();
        }
        else if (temp == 3) {
          display.clearDisplay();
          text("ANALOG", 29, 16);
          text("READ", 41, 42);
          display.display();
        }
        else if (temp == 4) {
          display.clearDisplay();
          text("DIGITAL", 23, 16);
          text("READ", 41, 42);
          display.display();
        }
        else if (temp == 5) {
          display.clearDisplay();
          text("SONAR READ", 5, 24);
          display.display();
        }
        else if (temp == 6) {
          display.clearDisplay();
          text("  COLOUR  ", 4, 16);
          text("   TEST   ", 4, 42);
          display.display();
        }
        else if (temp == 7) {
          display.clearDisplay();
          text("   MOVE   ", 04, 16);
          text(" STRAIGHT ", 04, 42);
          display.display();
        }
      }
      if (digitalRead(swr) == LOW) {
        while (digitalRead(swr) == LOW) {
          delay(1);
        }
        sust_cracker_nut();
        return 0;
      }
    }

    while (digitalRead(swl) == LOW) {
      delay(1);
    }
  }
  return temp;
}


int menu_function2() {
  int list = 6;
  int p = 0;
  int temp = 0;
  if (digitalRead(swr) == LOW) {
    while (digitalRead(swr) == LOW) {
      delay(1);
    }
    while (digitalRead(swr) == HIGH) {
      delay(1);
      p = map(analogRead(13), 0, 1000, 1, list);
      if (temp != p) {
        temp = p;
        if (temp == 1) {
          display.clearDisplay();
          text("COUNTER", 21, 16);
          text("SETUP", 35, 42);
          display.display();
        }
        else if (temp == 2) text_speed_adjust();
        else if (temp == 3) {
          display.clearDisplay();
          text("BRAKING", 23, 16);
          text("MECHANISM", 11, 42);
          display.display();
        }
        else if (temp == 4) {
          display.clearDisplay();
          text("  OTHER  ", 10, 16);
          text("ADJUSTMENT", 4, 42);
          display.display();
        }
        else if (temp == 5) {
          display.clearDisplay();
          text("BLUETOOTH", 11, 16);
          text("CONTROL", 23, 42);
          display.display();
        }
        else if (temp == 6) {
          display.clearDisplay();
          text("HEADLIGHT", 11, 16);
          text("CONTROL", 23, 42);
          display.display();
        }
      }
      if (digitalRead(swl) == LOW) {
        while (digitalRead(swl) == LOW) {
          delay(1);
        }
        sust_cracker_nut();
        return 0;
      }
    }

    while (digitalRead(swr) == LOW) {
      delay(1);
    }
  }
  return temp;
}
