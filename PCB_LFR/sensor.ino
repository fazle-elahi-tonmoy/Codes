void cal() {
  byte i = 0;
  for (i = 0; i < 6; i++) {
    maximum[i] = 0; minimum[i] = 1024;
  }
  motor(-100, 100);
  for (short int c = 0; c < 3000 ; c++)
    for (i = 0; i < 6; i++) {
      (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
      maximum[i] = max(maximum[i], s[i]);
      minimum[i] = min(minimum[i], s[i]);
    }
  motor(0, 0);
  for (i = 0; i < 6; i++) {
    thresould[i] = (maximum[i] - minimum[i]) * 0.5 + minimum[i];
    EEPROM.write(i, thresould[i] / 5 ); delay(10);
    EEPROM.write(i + 6, maximum[i] / 5 ); delay(10);
    EEPROM.write(i + 12, minimum[i] / 5 ); delay(10);
  }
  return;
}


void reading() {
  sensor = 0; //this is to refresh initial value
  sum = 0;
  for (int i = 0 ; i < 6 ; i++) {
    (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    (s[i] > 410) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
    sum += s[i]; //finds out total count of sensor
  }
}

void show_the_value() {
  reading();
  for (int i = 5 ; i >= 0 ; i--)
    Serial.print(String(s[i], 10) + " ");
  Serial.println(sonar.ping_cm());
}
