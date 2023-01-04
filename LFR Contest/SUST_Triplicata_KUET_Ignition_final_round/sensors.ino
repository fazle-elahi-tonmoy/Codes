void cal() {
  short int i = 0;
  motorSpeedR(250, 250);
  for (short int c = 0; c < 5000 ; c++)
    for (i = 0; i < 6; i++) {
      sensor[i] = analogRead(i + 8);
      maximum[i] = max(maximum[i], sensor[i]);
      minimum[i] = min(minimum[i], sensor[i]);
    }
  mos(0, 0);
  for (i = 0; i < 6; i++) {
    trash[i] = (maximum[i] - minimum[i]) * cal_p + minimum[i];
    EEPROM.write(i, trash[i] / 5 );
    delay(10);
  }
  return;
}


void check()
{
  sum = 0;
  bin = 0;
  for (short int i = 0; i < 6; i++) {
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

void debug() {
  for (short int i = 7; i >= 0 ; i--) {
    if (i == 4 || i == 5) continue;
    Serial.print(sensor[i]);
  }
  Serial.print("  ");
  Serial.print(sum);
  Serial.print("  ");
  Serial.print(bin);
  Serial.print("  ");
  Serial.print(sl);
  Serial.print("  ");
  Serial.print(sf);
  Serial.print("  ");
  Serial.println(sr);
}
