short int getclick() {
  short int t = 0, cl = 0;
  short int list = 3;
  if (digitalRead(rb) == LOW || digitalRead(lb) == LOW) {
    digitalWrite(12, HIGH);
    while (digitalRead(rb) == LOW || digitalRead(lb) == LOW) {
      delay(1);
      short int i = 0;
      while (digitalRead(rb) == LOW && digitalRead(lb) == LOW) {
        delay(1);
        i++;
        digitalWrite(13, HIGH);
        if (i > 200) {
          digitalWrite(13, LOW);
          digitalWrite(12, LOW);
          while (digitalRead(rb) == LOW && digitalRead(lb) == LOW);
          short int j = 0;
          while (digitalRead(rb) == LOW || digitalRead(lb) == LOW) {
            delay(1);
            j++;
            if (j > 200) {
              (digitalRead(rb) == LOW) ? digitalWrite(13, HIGH) : digitalWrite(12, HIGH);
              (digitalRead(rb) == LOW) ? j = 1 : j = 2;
              while (digitalRead(rb) == LOW || digitalRead(lb) == LOW);
              (j == 1) ? cal() : mos(10*spl, 10*spr);
              return list + 1;
            }
          }
          counter_adjust();
          return list + 1;
        }
      }
      digitalWrite(13, LOW);
      t++;
    }
    digitalWrite(12, LOW);
    while (t > 15) {
      if (cl != menu) {
        cl = menu;
        if (cl == 1) text_line_follow();
        else if (cl == 2) {
          display.clearDisplay();
          text("ANALOG", 29, 16);
          text("READ", 41, 42);
          display.display();
        }
        else if (cl == 3) {
          display.clearDisplay();
          text("SONAR READ", 5, 24);
          display.display();
        }
        //                else if (cl == 2) {
        //                  display.clearDisplay();
        //                  text("DIGITAL", 23, 16);
        //                  text("READ", 41, 42);
        //                  display.display();
        //                }
      }
      if (digitalRead(lb) == LOW) {
        short int t = 0;
        digitalWrite(12, HIGH);
        while (digitalRead(lb) == LOW) {
          delay(1);
          if (t > 200) {
            digitalWrite(12, LOW);
            while (digitalRead(lb) == LOW);
            return list + 1;
          }
          t++;
        }
        digitalWrite(12, LOW);
        if (t > 15) menu--;
        if (menu < 1) menu = list;
      }

      else if (digitalRead(rb) == LOW) {
        short int t = 0;
        digitalWrite(13, HIGH);
        while (digitalRead(rb) == LOW) {
          delay(1);
          if (t > 200) {
            while (digitalRead(rb) == LOW) digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);
            return cl;
          }
          t++;
        }
        digitalWrite(13, LOW);
        if (t > 15) menu++;
        if (menu > list) menu = 1;
      }
    }
  }
  return cl;
}
