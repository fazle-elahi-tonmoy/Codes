void arm_mode() {
  if (x == 'F') arm1_dir = -1;
  else if (x == 'B') arm1_dir = 1;
  else if (x == 'L') base_dir = 1;
  else if (x == 'R') base_dir = -1;
  else if (x == 'T') arm2_dir = -1;
  else if (x == 'D') arm2_dir = 1;
  else if (x >= '0' && x <= '9') {
    grab_pos = ('9' - x) * 10 + 45;
    Serial.println(grab_pos);
    grabber.write(grab_pos);
  } else {
    arm1_dir = arm2_dir = base_dir = 0;
  }
}