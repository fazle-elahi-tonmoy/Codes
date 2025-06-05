void remote_control() {
  while (1) {
    if (SerialBT.available() > 0) {
      char data = SerialBT.read();
      Serial.println(data);
      if (data == 'F') {
        motor(1);
        steering.write(st_mid);
      } else if (data == 'B') {
        motor(-1);
        steering.write(st_mid);
      } else if (data == 'G') {
        motor(1);
        steering.write(st_left);
      } else if (data == 'H') {
        motor(-1);
        steering.write(st_left);
      } else if (data == 'I') {
        motor(1);
        steering.write(st_right);
      } else if (data == 'J') {
        motor(-1);
        steering.write(st_right);
      } else if (data == 'L') {
        motor(0);
        steering.write(st_left);
      } else if (data == 'R') {
        motor(0);
        steering.write(st_right);
      }

      else if (data >= '0' && data <= '9') ledcWrite(10, map(data - '0', 0, 9, 50, 255));
      else if (data == 'S') motor(0);
    }
  }
}
