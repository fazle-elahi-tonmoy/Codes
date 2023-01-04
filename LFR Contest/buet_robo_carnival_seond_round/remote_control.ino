void remote_control() {
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      if (data == 'F')      mos(10 * spr, 10 * spl);
      else if (data == 'B') motorSpeedB(10 * spr, 10 * spl);
      else if (data == 'L') motorSpeedL(6 * spr, 6 * spl);
      else if (data == 'R') motorSpeedR(6 * spr, 6 * spl);
      else if (data == 'G') mos(10 * spr, 0);
      else if (data == 'I') mos(0, 10 * spl);
      else if (data == 'H') motorSpeedB(10 * spr, 0);
      else if (data == 'J') motorSpeedB(0, 10 * spl);
      else if (data == 'W') digitalWrite(calout, HIGH);
      else if (data == 'w') digitalWrite(calout, LOW);
      else if (data == 'U') digitalWrite(d30, HIGH);
      else if (data == 'u') digitalWrite(d30, LOW);
      else if (data == 'S') motorSpeedS();
    }
  }
}

