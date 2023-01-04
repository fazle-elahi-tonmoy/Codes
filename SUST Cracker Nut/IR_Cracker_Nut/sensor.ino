void cal() {
  motorSpeedR(150, 150);
  for (int c = 0; c < 3000 ; c++)
    for (int i = 0; i < 6; i++) {
      sensor[i] = analogRead(i);
      maximum[i] = max(maximum[i], sensor[i]);
      minimum[i] = min(minimum[i], sensor[i]);
    }
  motorSpeedS();
  for (int i = 0; i < 6; i++) trash[i] = (( maximum[i] - minimum[i]) * cal_p + minimum[i]);
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i, trash[i] / 5 );
    delay(10);
  }
  return;
}

void check()
{
  sum = 0;
  bin = 0;
  for (int i = 0; i < 6; i++) {
    sensor[i] = analogRead(i);
    if (mode == 1) (sensor[i] > trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    else if (mode == 0) (sensor[i] < trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    sum += sensor[i];
    bin += sensor[i] * bina[i];
  }
  return;
}

void sonar() {
  sl = sonarl.ping_cm();
  sf = sonarf.ping_cm();
  sr = sonarr.ping_cm();
}

char colour() {
  int R, G, B;
  char ch;


  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  delay(10);
  R = pulseIn (out, LOW);
  //G
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  delay(10);
  G = pulseIn (out, LOW);
  //B
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  delay(10);
  B = pulseIn (out, LOW);

  if (R < G && R < B) ch = 'r';
  if (B < G && R > B) ch = 'b';
  if (R > G && G < B) ch = 'g';
  return ch;
}

void debug() {
  for (int i = 5; i >= 0 ; i--) {
    Serial.print(sensor[i]);
  }
  Serial.print("  ");
  Serial.print(mov);
  Serial.print("  ");
  Serial.print(sl);
  Serial.print("  ");
  Serial.print(sf);
  Serial.print("  ");
  Serial.println(sr);
}

int ltouch() {
  if (analogRead(9) > 200) return 1;
  else return 0;
}

int rtouch() {
  if (analogRead(8) > 200) return 1;
  else return 0;
}
