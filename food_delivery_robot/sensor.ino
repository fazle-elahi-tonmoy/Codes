void reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] > threshold) ? s[i] = 1 : s[i] = 0;
    sensor += s[i] * (i + 1);
    sum += s[i];
  }
  if (sum) avg = (float)sensor / sum;
  error = 3.5 - avg;
  ss[0] = analogRead(6);
  ss[1] = analogRead(7);
  (ss[0]>500)? ss[0] = 0 : ss[0] = 1;
  (ss[1]>500)? ss[1] = 0 : ss[1] = 1;
}

void show_analog_value() {
  while (1) {
    for (byte i = 0; i < 6; i++) {
      Serial.print(analogRead(i));
      Serial.print(" ");
    }
    Serial.println();
  }
}


void show_digital_value() {
  while (1) {
    reading();
    for (byte i = 0; i < 6; i++) {
      Serial.print(s[i]);
      Serial.print(" ");
    }
    Serial.print("    ");
    Serial.println(error);
  }
}

void sonar_read() {
  if (millis() - sonar_timer > 30) {
    sonar_timer = millis();
    distance = sonar.ping_cm();
    if (distance <= 0) distance = 20;
  }
}
