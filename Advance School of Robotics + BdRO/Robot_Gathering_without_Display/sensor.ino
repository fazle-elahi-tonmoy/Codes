void reading() {
  sensor = 0; //this is to refresh initial value
  sum = 0;
  for (int i = 0 ; i < 6 ; i++) {
    s[i] = analogRead(i);
    (s[i] > thresould[i]) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
    sum += s[i]; //finds out total count of sensor
  }
}

void callibration() {
  motor(-100, 100);
  for (int i = 0; i < 6; i++) {
    maximum[i] = 0;
    minimum[i] = 1024;
  }
  for (int c = 0; c < 5000 ; c++)
    for (int i = 0 ; i < 6 ; i++) {
      s[i] = analogRead(i);
      if (s[i] > maximum[i]) maximum[i] = s[i];
      if (s[i] < minimum[i]) minimum[i] = s[i];
    }

  motor(0, 0);
  for (int i = 0 ; i < 6 ; i++) {
    thresould[i] = minimum[i] + (maximum[i] - minimum[i]) * 0.4;
    EEPROM.update(i, minimum[i]/4);
    EEPROM.update(i+6, thresould[i]/4);
    EEPROM.update(i+12, maximum[i]/4);
  }
}

void digital_value() {
  reading();
  for (int i = 5 ; i >= 0 ; i--)
    Serial.print(String(s[i], 10) + " ");
  Serial.println(sensor);
}

void analog_value() {
  for (int i = 0 ; i < 6 ; i++) s[i] = analogRead(i);
  for (int i = 5 ; i >= 0 ; i--)
    Serial.print(String(s[i]) + " ");
  Serial.println();
}
