void counter_adjust() {
  short int cl = -1;
  short int list = 9;
  short int temp = counter;
  while (1) {
    if (cl != counter) {
      cl = counter;
      display.clearDisplay();
      value = String(cl, 10);
      text("COUNTER:", 10, 24);
      text(value, 110, 24);
      display.display();
    }

    if (digitalRead(lb) == LOW) {
      short int t = 0;
      digitalWrite(12, HIGH);
      while (digitalRead(lb) == LOW) {
        delay(1);
        if (t > 200) {
          digitalWrite(12, LOW);
//          display.clearDisplay();
//          text("BYE!!!", 29, 24);
//          display.display();
          counter = temp;
          return;
        }
        t++;
      }
      digitalWrite(12, LOW);
      if (t > 15 && counter > 0) counter--;
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
          EEPROM.write(6, counter);
          display.clearDisplay();
          text("DONE!!!", 23, 24);
          display.display();
          return;
        }
        t++;
      }
      digitalWrite(13, LOW);
      if (t > 15 && counter < list) counter++;
    }
  }
}
