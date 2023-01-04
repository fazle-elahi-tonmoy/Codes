void remote_control() {
  byte spd = 10;
  while (1) {
    if (Serial.available() > 0) {
      char data =  Serial.read();
      Serial.println(data);
      if (data == 'F')      motor(25 * spd, 25 * spd);
      else if (data == 'B') motor(-25 * spd, -25 * spd);
      else if (data == 'L') motor(-255, 255);
      else if (data == 'R') motor(255, -255);
      else if (data == 'I') motor(25 * spd, 0);
      else if (data == 'G') motor(0, 25 * spd);
      else if (data == 'J') motor(-25 * spd, 0);
      else if (data == 'H') motor(0, -25 * spd);
      else if (data == 'W') lift.write(lower); //headlight on
      else if (data == 'w') lift.write(rise); //headlight off
      else if (data == 'U') ; //backlight on
      else if (data == 'u') ; //backlight off
      else if (data == 'V') ;
      else if (data == 'v') ;
      else if (data == 'X') hand.write(grab);
      else if (data == 'x') hand.write(drop);
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
      else if (data == 'S') motor(0, 0);
    }
  }
}
