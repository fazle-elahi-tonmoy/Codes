void motor_mode() {
  if (x == 'F') motor(1, 1);
  else if (x == 'B') motor(-1, -1);
  else if (x == 'L') motor(-1, 1);
  else if (x == 'R') motor(1, -1);
  else if (x == 'G') motor(0, 1);
  else if (x == 'H') motor(0, -1);
  else if (x == 'I') motor(1, 0);
  else if (x == 'J') motor(-1, 0);
  else if (x == 'S') motor(0, 0);
  else if (x == 'W') digitalWrite(pump, 1);
  else if (x == 'w') digitalWrite(pump, 0);
  else if (x >= '0' && x <= '9') {
    speed = map((x - '0'), 0, 9, 100, 250);
    ledcWrite(0, speed);
    ledcWrite(1, speed);
  }
}