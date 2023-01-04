void remote_control() {
  delay(100);
  while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      if (data == 'F')      mos(10 * spl, 10 * spr);
      else if (data == 'B') motorSpeedB(10 * spl, 10 * spr);
      else if (data == 'L') motorSpeedL(6 * spl, 6 * spr);
      else if (data == 'R') motorSpeedR(6 * spl, 6 * spr);
      else if (data == 'I') mos(10 * spl, 0);
      else if (data == 'G') mos(0, 10 * spr);
      else if (data == 'J') motorSpeedB(10 * spl, 0);
      else if (data == 'H') motorSpeedB(0, 10 * spr);
      else if (data == 'W') digitalWrite(13, HIGH);
      else if (data == 'U') digitalWrite(13, LOW);
      else if (data == 'S') mos(0, 0);
    }
  }
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  while (digitalRead(lb) == LOW || digitalRead(rb) == LOW);
}
