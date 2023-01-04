void grab(byte a) {
  motor(0, 0);
  left_hand.write(lpos[a]);
  right_hand.write(rpos[a]);
  delay(1000);
  counter++;
}

void release() {
  motor(0, 0);
  left_hand.write(lpos[0]);
  right_hand.write(rpos[0]);
  delay(1000);
//  while(1);
  if (cross != s) {
    (cross == 'l') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
    while (s[1] + s[2] + s[3] + s[4]) reading();
    while (s[2] == 0 && s[3] == 0) reading();
    while (s[2] + s[3]) reading();
    while (s[2] == 0 && s[3] == 0) reading();
    (cross == 'r') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
    delay(turn_brake);
  }
  else {
    (flag == 'r') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
    while (s[2] == 0 && s[3] == 0) reading();
    if (t_section) {
      while (s[2] + s[3]) reading();
      while (s[2] == 0 && s[3] == 0) reading();
    }
    (flag == 'l') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
    delay(turn_brake);
  }

  cross = 's'; flag = 's'; pos = 0; t_section = 0;
  counter++;
}
