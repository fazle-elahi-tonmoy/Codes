void bluetooth() {
  int s = 10; char x;
  while (1) {
    if (Serial.available() > 0) {
      x = Serial.read();
      if (x == 'F') motor(s * spl, s * spr);
      else if (x == 'B') motor(-s * spl, -s * spr);
      else if (x == 'L') motor(-s * spl, s * spr);
      else if (x == 'R') motor(s * spl, -s * spr);
      else if (x == 'G') motor(0, s * spr);
      else if (x == 'I') motor(s * spl, 0);
      else if (x == 'H') motor(0, -s * spr);
      else if (x == 'J') motor(-s * spl, 0);
      else if (x == 'S') motor(0, 0);
      else if (x == 'W') headlight(1);
      else if (x == 'w') headlight(0);
      else if (x == '0') s = 0;
      else if (x == '1') s = 1;
      else if (x == '2') s = 2;
      else if (x == '3') s = 3;
      else if (x == '4') s = 4;
      else if (x == '5') s = 5;
      else if (x == '6') s = 6;
      else if (x == '7') s = 7;
      else if (x == '8') s = 8;
      else if (x == '9') s = 9;
      else if (x == 'q') s = 10;
    }
  }
}
