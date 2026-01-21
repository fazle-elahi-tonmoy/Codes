void motor_mode() {
  if (x == 'F') motor(speed, speed);
  else if (x == 'B') motor(-speed, -speed);
  else if (x == 'L') motor(-speed, speed);
  else if (x == 'R') motor(speed, -speed);
  else if (x == 'G') motor(0, speed);
  else if (x == 'H') motor(0, -speed);
  else if (x == 'I') motor(speed, 0);
  else if (x == 'J') motor(-speed, 0);
  else if (x >= '0' && x <= '9') {
    int spd = x - '0';
    speed = map(spd, 0, 9, 100, 255);
    ledcWrite(0, abs(speed));
    ledcWrite(1, abs(speed));
  }

  if (x == 'S') motor(0, 0);
}