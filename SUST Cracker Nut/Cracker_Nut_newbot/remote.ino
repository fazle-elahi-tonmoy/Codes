void remote_control() {
  int spd = 10;
  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      Serial.println(data);
      if (data == 'F')      mos(25 * spd, 25 * spd);
      else if (data == 'B') motorSpeedB(25 * spd, 25 * spd);
      else if (data == 'L') motorSpeedL(25 * spd,  25 * spd);
      else if (data == 'R') motorSpeedR(25 * spd,  25 * spd);
      else if (data == 'G') mos(25 * spd, 0);
      else if (data == 'I') mos(0, 25 * spd);
      else if (data == 'H') motorSpeedB(25 * spd, 0);
      else if (data == 'J') motorSpeedB(0, 25 * spd);
      else if (data == 'W') digitalWrite(light, HIGH);
      else if (data == 'w') digitalWrite(light, LOW);
      else if (data == 'U') analogWrite(7, 255);
      else if (data == 'u') analogWrite(7, 0);
      else if (data == 'S') mos(0, 0);
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
      else if(data == 'D') break;
    }
  }
}
