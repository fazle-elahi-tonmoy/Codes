void command() {
  if (x == 'F') motor(s * spdl, s * spdr);
  else if (x == 'B') motor(-s * spdl, -s * spdr);
  else if (x == 'L') motor(-s * spdl, s * spdr);
  else if (x == 'R') motor(s * spdl, -s * spdr);
  else if (x == 'G') motor(0, s * spdr);
  else if (x == 'I') motor(s * spdl, 0);
  else if (x == 'H') motor(0, -s * spdr);
  else if (x == 'J') motor(-s * spdl, 0);
  else if (x == 'S') motor(0, 0);
  else if (x == 'W') digitalWrite(front_light, HIGH);
  else if (x == 'w') digitalWrite(front_light, LOW);
  else if (x == 'U') digitalWrite(back_light, HIGH);
  else if (x == 'u') digitalWrite(back_light, LOW);
  else if (x == 'X') mode = 1;
  else if (x == 'x') mode = 0;
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
