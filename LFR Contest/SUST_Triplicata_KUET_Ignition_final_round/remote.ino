void remote_control() {
  display.clearDisplay();
  text("ACTIVATED", 10, 24);
  display.display();
  while (digitalRead(mb) == HIGH) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      if (data == 'F')      mos(10 * spl, 10 * spr);
      else if (data == 'B') motorSpeedB(10 * spl, 10 * spr);
      else if (data == 'L') motorSpeedL(10 * spl, 10 * spr);
      else if (data == 'R') motorSpeedR(10 * spl, 10 * spr);
      else if (data == 'I') mos(10 * spl, 0);
      else if (data == 'G') mos(0, 10 * spr);
      else if (data == 'J') motorSpeedB(10 * spl, 0);
      else if (data == 'H') motorSpeedB(0, 10 * spr);
      else if (data == 'W') head_light(1);
      else if (data == 'w') head_light(0);
      else if (data == 'U') digitalWrite(red, HIGH);
      else if (data == 'u')digitalWrite(red, LOW);
      else if (data == 'V') digitalWrite(7, HIGH);
      else if (data == 'v')digitalWrite(7, LOW);
      else if (data == 'S') mos(0, 0);
    }
  }
  while (digitalRead(mb) == LOW);
}
