byte logo_bmp[] = { B00000000, B11000000, B00000001, B11000000,
                    B00000001, B11000000, B00000011, B11100000,
                    B11110011, B11100000, B11111110, B11111000,
                    B01111110, B11111111, B00110011, B10011111,
                    B00011111, B11111100, B00001101, B01110000,
                    B00011011, B10100000, B00111111, B11100000,
                    B00111111, B11110000, B01111100, B11110000,
                    B01110000, B01110000, B00000000, B00110000
                  };

void text(String t, short int x, short int y) {
  display.setCursor(x, y);
  display.print(t);
}

void sust_triplicata() {
  display.clearDisplay();
  display.drawBitmap(5, 0, logo_bmp, 16, 16, 1);
  display.drawBitmap(110, 0, logo_bmp, 16, 16, 1);
  text("SUST", 41, 18);
  text("TRIPLICATA", 5, 35);
  for (int i = 48; i <= 64 ; i += 4) {
    display.drawLine(i, 0, i - 48, 32, WHITE);
    display.drawLine(i + 16, 0, i + 68, 32, WHITE);
  }
  for (int i = 52 ; i <= 64 ; i += 2) display.drawLine(0, i, 128, i, WHITE);
  for (int i = 0 ; i <= 2 ; i += 2) {
    display.drawLine(i, 32, i, 52, WHITE);
    display.drawLine(127 - i, 32, 127 - i, 52, WHITE);
  }
  display.display();
}


void analog_reading_display() {
  short int i = 0;
  short int s[] = {0, 0, 0, 0, 0, 0};
  display.clearDisplay();
  for (i = 0; i < 6; i++) {
     s[i] = analogRead(i+8);
  }
  for (i = 0; i < 3 ; i++) {
    value = String(s[i], 10);
    text(value, 72, 46 - (i * 22));
  }
  for (i = 3; i < 6; i++) {
    value = String(s[i], 10);
    text(value, 12,  (i * 22) - 64);
  }
  display.display();
}

void digital_reading_display() {
  display.clearDisplay();
  check();
  for (short int i = 5; i >= 0; i--) {
    value = String(sensor[i], 2);
    text(value, 115 - (i * 23), 2);
  }
  value = String(sum, 10);
  text("sum = ", 0, 24);
  text(value, 70, 24);
  value = String(bin, 10);
  text("bin = ", 0, 46);
  text(value, 70, 46);
  display.display();
}

void text_line_follow() {
  display.clearDisplay();
  text("LineFollow", 4, 16);
  text("Counter:", 10, 42);
  value = String(counter, 10);
  text(value, 104, 42);
  display.display();
}

void text_speed_adjust() {
  display.clearDisplay();
  text("SPEED", 35, 2);
  text("ADJUST", 29, 24);
  text("L:   R:  ", 11, 46);
  int p = spl;
  String value = String(p, 10);
  text(value, 33, 46);
  p = spr;
  value = String(p, 10);
  text(value, 93, 46);
  display.display();
}

void sonar_reading_display() {
  sonar();
  display.clearDisplay();
  text("L", 12, 16);
  text("F", 59, 16);
  text("R", 106, 16);
  value = String(sl, 10);
  text(value, 5, 44);
  value = String(sf, 10);
  text(value, 52, 44);
  value = String(sr, 10);
  text(value, 99, 44);
  display.display();
}

void light_control() {
  int cl = -1;
  while (digitalRead(mb) == HIGH) {
    if (cl != head) {
      cl = head;
      if (cl == 1) {
        display.clearDisplay();
        text("    ON    ", 4, 22);
        display.display();
        head_light(cl);
      }
      else if (cl == 0) {
        display.clearDisplay();
        text("   OFF   ", 10, 22);
        display.display();
        head_light(cl);
      }
    }
    if (digitalRead(ub) == LOW) head = 1;
    else if (digitalRead(db) == LOW) head = 0;
  }
  while (digitalRead(mb) == LOW);
}

void text_callibrating() {
  short int i, t = 0;
  display.clearDisplay();
  text("CALLIBRATE", 04, 16);
  display.display();
  for (i = 56; i >= 0; i -= 18) {
    if (digitalRead(mb) == LOW) break;
    text(".", i, 40);
    text(".", 112 - i, 40);
    display.display();
  }
  if (i <= 2 ) cal();

  //for showing the thresould value
  display.clearDisplay();
  text("MID VALUE", 9, 0);
  for (i = 0; i < 3 ; i++) {
    value = String(trash[i], 10);
    text(value, 72,  48 - (i * 16));
  }
  for (i = 3; i < 6; i++) {
    value = String(trash[i], 10);
    text(value, 12,  (i * 16) - 32);
  }
  display.display();
  while (digitalRead(mb) == LOW);
  while (digitalRead(mb) == HIGH);
  //...........................................................................................
  display.clearDisplay();
  text("MINIMUM", 26, 0);
  for (i = 0; i < 3 ; i++) {
    value = String(minimum[i], 10);
    text(value, 72,  48 - (i * 16));
  }
  for (i = 3; i < 6; i++) {
    value = String(minimum[i], 10);
    text(value, 12,  (i * 16) - 32);
  }
  display.display();
  while (digitalRead(mb) == LOW);
  while (digitalRead(mb) == HIGH);
  //........................................................................................
  display.clearDisplay();
  text("MAXIMUM", 26, 0);
  for (i = 0; i < 3 ; i++) {
    value = String(maximum[i], 10);
    text(value, 72,  48 - (i * 16));
  }
  for (i = 3; i < 6; i++) {
    value = String(maximum[i], 10);
    text(value, 12,  (i * 16) - 32);
  }
  display.display();
  while (digitalRead(mb) == LOW);
  while (digitalRead(mb) == HIGH);

}
