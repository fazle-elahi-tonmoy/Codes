void cal() {
  byte i = 0;
  motorSpeedL(100, 100);
  for (short int c = 0; c < 3000 ; c++)
    for (i = 0; i < 6; i++) {
      sensor[i] = analogRead(i + 8);
      maximum[i] = max(maximum[i], sensor[i]);
      minimum[i] = min(minimum[i], sensor[i]);
    }
  mos(0, 0);
  for (i = 0; i < 6; i++) {
    trash[i] = (maximum[i] - minimum[i]) * cal_p + minimum[i];
    EEPROM.write(i, trash[i] / 5 ); delay(10);
    EEPROM.write(i + 38, maximum[i] / 5 ); delay(10);
    EEPROM.write(i + 44, minimum[i] / 5 ); delay(10);
  }
  return;
}


void check()
{
  sum = 0;
  bin = 0;
  for (byte i = 0; i < 6; i++) {
    sensor[i] = analogRead(i + 8);
    if (mode == 1) (sensor[i] > trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    else if (mode == 0) (sensor[i] < trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    sum += sensor[i];
    bin += sensor[i] * bina[i];
  }
  return;
}

void sonar() {
  sf = sonarf.ping_cm();
  sr = sonarr.ping_cm();
  sl = sonarl.ping_cm();
}

void sensor_display() {
  byte cl = 0, list = 5, m = 1;
  while (1) {
    if (cl != m) {
      cl = m;
      display.clearDisplay();
      if (cl == 1) text("CALIBRATE", 10, 25);
      else if (cl == 2) {
        text("  ANALOG  ", 04, 12);
        text("   READ   ", 04, 38);
      }
      else if (cl == 3) {
        text(" DIGITAL ", 10, 12);
        text("   READ   ", 04, 38);
      }
      else if (cl == 4) text("SONAR READ", 04, 25);
      else if (cl == 5) {
        text("  SERIAL  ", 04, 12);
        text("   READ   ", 04, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && m < list) {
      delay(100);
      m++;
    }
    else if (digitalRead(db) == LOW && m > 1) {
      delay(100);
      m--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) return;
      else {
        if (cl == 1) text_callibrating();
        else if (cl == 2) while (digitalRead(mb) == HIGH) analog_reading_display() ;
        else if (cl == 3) while (digitalRead(mb) == HIGH) digital_reading_display() ;
        else if (cl == 4) while (digitalRead(mb) == HIGH) sonar_reading_display() ;
        else if (cl == 5) serial_reading_display() ;
        while (digitalRead(mb) == LOW);
        cl = 0;
      }
    }
  }
}
