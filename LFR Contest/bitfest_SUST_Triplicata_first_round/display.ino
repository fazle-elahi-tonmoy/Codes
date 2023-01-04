void text(String t, short int x, short int y) {
  display.setCursor(x, y);
  display.print(t);
}

void sust_triplicata() {
  short int i = 0;
  display.clearDisplay();
  display.setTextSize(2);
  text("SUST", 41, 18);
  text("TRIPLICATA", 5, 35);
  for (i = 48; i <= 64 ; i += 4) {
    display.drawLine(i, 0, i - 48, 32, WHITE);
    display.drawLine(i + 16, 0, i + 68, 32, WHITE);
  }
  for (i = 52 ; i <= 64 ; i += 2) display.drawLine(0, i, 128, i, WHITE);
  for (i = 0 ; i <= 2 ; i += 2) {
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
    (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
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

void text_callibrating() {
  short int i, t = 0;
  display.clearDisplay();
  display.setTextSize(1);
  text("CALLIBRATING", 20, 24);
  display.display();
  for (i = 95; i <= 105; i += 5) {
    while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) {
      t++;
      delay(1);
      if (t == 500) {
        t = 0;
        break;
      }
    }
    if (digitalRead(rb) == LOW || digitalRead(lb) == LOW) break;
    text(".", i, 24);
    display.display();
  }
  if (i >= 110) cal();
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  display.clearDisplay();
  //for showing the thresould value
  for (i = 0; i < 6 ; i++) {
    value = String(minimum[i], 10);
    if (i >= 0 && i <= 2) {
      text(value,  32 + (i * 32), 0);
    }
    if (i >= 3 && i <= 5) {
      text(value, (i * 32) - 64, 10);
    }
  }

  for (i = 0; i < 6 ; i++) {
    value = String(trash[i], 10);
    if (i >= 0 && i <= 2) {
      text(value,  32 + (i * 32), 23);
    }
    if (i >= 3 && i <= 5) {
      text(value, (i * 32) - 64, 33);
    }
  }

  for (i = 0; i < 6 ; i++) {
    value = String(maximum[i], 10);
    if (i >= 0 && i <= 2) {
      text(value,  32 + (i * 32), 46);
    }
    if (i >= 3 && i <= 5) {
      text(value, (i * 32) - 64, 56);
    }
  }
  text("MIN", 8, 5);
  text("MID", 8, 28);
  text("MAX", 8, 51);
  display.drawLine(0, 20, 128, 20, WHITE);
  display.drawLine(0, 43, 128, 43, WHITE);
  display.display();
  delay(500);
  while (digitalRead(rb) == HIGH && digitalRead(lb) == HIGH);

}
