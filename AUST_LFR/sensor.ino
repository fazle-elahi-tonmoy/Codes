void reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] > threshold[i]) ? s[i] = 1 : s[i] = 0;  //this line converts analog value into digital
    sensor += s[i] * base[i];
    sum += s[i];
  }
}

void cal() {
  byte i = 0;
  for (i = 0; i < 6; i++) {
    maximum[i] = 0;
    minimum[i] = 1024;
  }
  motor(-100, 100);
  for (short int c = 0; c < 3000; c++)
    for (i = 0; i < 6; i++) {
      s[i] = analogRead(i);
      maximum[i] = max(maximum[i], s[i]);
      minimum[i] = min(minimum[i], s[i]);
    }
  motor(0, 0);
  for (i = 0; i < 6; i++) {
    threshold[i] = (maximum[i] - minimum[i]) * 0.5 + minimum[i];
    EEPROM.write(i, threshold[i] / 4);
    delay(10);
    EEPROM.write(i + 6, maximum[i] / 4);
    delay(10);
    EEPROM.write(i + 12, minimum[i] / 4);
    delay(10);
  }
  return;
}


void show_analog_value() {
  for (short int i = 5; i >= 0; i--) Serial.print(String(analogRead(i)) + " ");
  Serial.println();
}
