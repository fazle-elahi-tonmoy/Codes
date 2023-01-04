void reading() {
  sensor = 0; //this is to refresh initial value
  sum = 0;
  for (int i = 0 ; i < 6 ; i++) {
    s[i] = analogRead(i);
    (s[i] > mid[i]) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
    sum += s[i]; //finds out total count of sensor
  }
}

void show_the_value() {
  reading();
  for (int i = 5 ; i >= 0 ; i--)
    Serial.print(String(s[i], 10) + " ");
  Serial.println(sensor);
}


void cal() {
  for (int i = 0; i < 6 ; i++) {
    maximum[i] = 0;
    minimum[i] = 1023;
  }
  int c = 0;
  motor(100, -100);
  while (c < 5000) {
    c++;
    for (int i = 0; i < 6; i++) {
      s[i] = analogRead(i);
      maximum[i] = max(s[i], maximum[i]);
      minimum[i] = min(s[i], minimum[i]);
    }
  }
  motor(0, 0);
  for (int i = 0; i < 6; i++) {
    mid[i] = (minimum[i] + maximum[i]) / 2;
    EEPROM.write(i, mid[i] / 5); delay(10);
    EEPROM.write(i+6, maximum[i] / 5); delay(10);
    EEPROM.write(i+12, minimum[i] / 5); delay(10);
  }
}
