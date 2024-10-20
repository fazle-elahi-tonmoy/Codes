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
    speed = (x - '0') * 17 + 100;
    ledcWrite(14, speed);
    ledcWrite(15, speed);
  } else motor(0, 0);
}