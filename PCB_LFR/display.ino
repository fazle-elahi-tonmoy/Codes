void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}

void intro() {
  oled.set2X(); oled.clear();
  oled.setFont(System5x7);
  text("  TALOS", 10, 2);
  oled.set1X();
  text("         MINI", 0, 4);
  text("developed by ROBOADDA", 0, 7);
  oled.set2X();
}

void analogReadDisp() {
  byte i;
  oled.set2X(); oled.clear();
  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
    for (i = 0; i < 6; i++)  (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    for (i = 0; i < 3 ; i++) {
      value = String(s[i]);
      (s[i] < 100) ? text(value + "  ", 70, 5 - i * 2) : text(value + " ", 70, 5 - i * 2);
    }
    for (i = 3; i < 6 ; i++) {
      value = String(s[i], 10);
      (s[i] < 100) ? text(value + "  ", 10, (i - 3) * 2 + 1) : text(value + " ", 10, (i - 3) * 2 + 1);
    }
  }
  intro();
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}

void sensordisp() {
  byte i;
  oled.set2X(); oled.clear();
  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
    reading();
    distance = sonar.ping_cm();
    for (short int i = 5; i >= 0; i--) {
      value = String(s[i], 2);
      text(value, 115 - (i * 23) , 2);
    }
    value = String(distance, 10);
    (distance < 10) ? text("sonar: " + value + " " , 4, 5) : text("sonar: " + value, 4, 5);
  }
  intro();
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}

void callibration() {
  byte i;
  oled.clear(); oled.set2X();
  text(" STARTING ", 4, 3);
  m1 = m2 = millis();
  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
    m2 = millis();
    if (m2 - m1 > 1000) {
      cal();
      break;
    }
  }
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW) digitalWrite(light, 1);
  digitalWrite(light, 0);
  //for showing the thresould value
  oled.clear(); oled.set1X();
  for (byte i = 0; i < 6 ; i++) {
    value = String(minimum[i], 10);
    if (i >= 0 && i <= 2) text(value,  32 + (i * 32), 0);
    if (i >= 3 && i <= 5) text(value, (i * 32) - 64, 1);
  }
  for (byte i = 0; i < 6 ; i++) {
    value = String(thresould[i], 10);
    if (i >= 0 && i <= 2) text(value,  32 + (i * 32), 2);
    if (i >= 3 && i <= 5) text(value, (i * 32) - 64, 3);
  }
  for (byte i = 0; i < 6 ; i++) {
    value = String(maximum[i], 10);
    if (i >= 0 && i <= 2) text(value,  32 + (i * 32), 4);
    if (i >= 3 && i <= 5) text(value, (i * 32) - 64, 5);
  }
  text("MIN", 8, 0); text("MID", 8, 2); text("MAX", 8, 4);

  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH);
  intro();
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}
