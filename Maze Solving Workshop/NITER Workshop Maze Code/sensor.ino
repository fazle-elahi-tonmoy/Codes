void reading() {
  sensor = 0, sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] >= mid[i]) ? s[i] = 1^inverse : s[i] = 0^inverse;
    sensor += s[i] * base[i];
    sum += s[i];
  }
}

void show_analog() {
  for (int i = 5; i >= 0; i--) {
    Serial.print(analogRead(i));
    Serial.print(" ");
  }
  Serial.println();
}

void show_digital() {
  reading();
  // for (int i = 5; i >= 0; i--) {
  //   Serial.print(s[i]);
  //   Serial.print(" ");
  // }
  Serial.println(sensor, BIN);
}