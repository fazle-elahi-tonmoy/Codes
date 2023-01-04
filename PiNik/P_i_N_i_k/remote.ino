void remote_control() {
  display.clearDisplay();
  text("ACTIVATED!", 4, 24);
  display.display();
  byte spd = 10;
  while (digitalRead(mb) == HIGH) {
    if (Serial.available() > 0) {
      char data = Serial.read();
      Serial.println(data);
      if (data == 'F') mos(25 * spd, 25 * spd);
      else if (data == 'B') mos(-25 * spd, -25 * spd);
      else if (data == 'L') mos(-25 * spd, 25 * spd);
      else if (data == 'R') mos(25 * spd, -25 * spd);
      else if (data == 'I') mos(25 * spd, 0);
      else if (data == 'G') mos(0, 25 * spd);
      else if (data == 'J') mos(-25 * spd, 0);
      else if (data == 'H') mos(0, -25 * spd);
      else if (data == 'W') head_light(1);
      else if (data == 'w') head_light(0);
      else if (data == 'U') {
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
      } else if (data == 'u') {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      } else if (data == 'V') digitalWrite(buzzer, HIGH);
      else if (data == 'v') digitalWrite(buzzer, LOW);
      else if (data == 'X') {
        lfang.write(fl);
        rfang.write(fr);
      } else if (data == 'x') {
        lfang.write(intl);
        rfang.write(intr);
      } else if (data >= '0' && data <= '9') spd = data - '0';
      else if (data == 'q') spd = 10;
      else if (data == 'S') mos(0, 0);
      else if (data == 'D') break;
    }
  }
  head_light(0);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(buzzer, LOW);
  lfang.write(intl);
  rfang.write(intr);
  while (digitalRead(mb) == LOW)
    ;
}
