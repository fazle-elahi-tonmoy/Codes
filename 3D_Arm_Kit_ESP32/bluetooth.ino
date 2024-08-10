void bluetooth_command() {
  if (SerialBT.available()) {
    char x = SerialBT.read();
    Serial.println(x);
    if (x == 'F') {
      arm1_dir = -1;
      base_dir = 0;
    } else if (x == 'B') {
      arm1_dir = 1;
      base_dir = 0;
    } else if (x == 'L') {
      arm1_dir = 0;
      base_dir = -1;
    } else if (x == 'R') {
      arm1_dir = 0;
      base_dir = 1;
    } else if (x == 'G') {
      arm1_dir = -1;
      base_dir = -1;
    } else if (x == 'H') {
      arm1_dir = 1;
      base_dir = -1;
    } else if (x == 'I') {
      arm1_dir = -1;
      base_dir = 1;
    } else if (x == 'J') {
      arm1_dir = 1;
      base_dir = 1;
    } else if (x == 'S') {
      arm1_dir = 0;
      base_dir = 0;
    } else if (x == 'T' || x == 'W') arm2_dir = 1;
    else if (x == 'D' || x == 'U') arm2_dir = -1;
    else if (x == 'N' || x == 'w' || x == 'u') arm2_dir = 0;
    else if (x >= '0' && x <= '9') {
      int pos = '9' - x;
      pos = map(pos, 0, 9, grab_close, grab_open);
      grab.write(pos);
    }
  }
}