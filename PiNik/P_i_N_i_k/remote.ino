void remote_control() {
  display.clearDisplay();
  text("ACTIVATED!", 4, 24);
  display.display();
  byte spd = 10;
  while (digitalRead(mb) == HIGH) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      Serial.println(data);
      if (data == 'F')      mos(25 * spd, 25 * spd);
      else if (data == 'B') motorSpeedB(25 * spd, 25 * spd);
      else if (data == 'L') motorSpeedL(25 * spd, 25 * spd);
      else if (data == 'R') motorSpeedR(25 * spd, 25 * spd);
      else if (data == 'I') mos(25 * spd, 0);
      else if (data == 'G') mos(0, 25 * spd);
      else if (data == 'J') motorSpeedB(25 * spd, 0);
      else if (data == 'H') motorSpeedB(0, 25 * spd);
      else if (data == 'W') head_light(1);
      else if (data == 'w') head_light(0);
      else if (data == 'U') {
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
      }
      else if (data == 'u') {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      else if (data == 'V') digitalWrite(buzzer, HIGH);
      else if (data == 'v') digitalWrite(buzzer, LOW);
      else if (data == 'X') {
        lfang.write(fl);
        rfang.write(fr);
      }
      else if (data == 'x') {
        lfang.write(intl);
        rfang.write(intr);
      }
      else if (data == '0') spd = 0;
      else if (data == '1') spd = 1;
      else if (data == '2') spd = 2;
      else if (data == '3') spd = 3;
      else if (data == '4') spd = 4;
      else if (data == '5') spd = 5;
      else if (data == '6') spd = 6;
      else if (data == '7') spd = 7;
      else if (data == '8') spd = 8;
      else if (data == '9') spd = 9;
      else if (data == 'q') spd = 10;
      else if (data == 'S') mos(0, 0);
      else if(data == 'D') break;
    }
  }
  head_light(0);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(buzzer, LOW);
  lfang.write(intl);
  rfang.write(intr);
  while (digitalRead(mb) == LOW);
}
