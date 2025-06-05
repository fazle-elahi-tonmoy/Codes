void motor_mode() {
  if (x == 'F') motor(speed, speed);
  else if (x == 'B') motor(-speed, -speed);
  else if (x == 'L') motor(-speed, speed);
  else if (x == 'R') motor(speed, -speed);
  else if (x == 'G') motor(0, speed);
  else if (x == 'H') motor(0, -speed);
  else if (x == 'I') motor(speed, 0);
  else if (x == 'J') motor(-speed, 0);
  else if (x >= '0' && x <= '9') base.write((x - '0') * 20);
  else if (x >= 'k' && x <= 't') top.write(45 + (x - 'k') * 10);
  else if (x == 'S') motor(0, 0);
}