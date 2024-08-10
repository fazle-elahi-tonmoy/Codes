void remote_control() {
  if (SerialBT.available() > 0) {
    char data = SerialBT.read();
    Serial.println(data);
    if (data != 'S') idle = 1;
    if (data == 'F') motor(1, 1);
    else if (data == 'B') motor(-1, -1);
    else if (data == 'L') motor(-1, 1);
    else if (data == 'R') motor(1, -1);
    else if (data == 'G' || data == 'g') motor(0, 1);
    else if (data == 'H' || data == 'h') motor(0, -1);
    else if (data == 'I' || data == 'i') motor(1, 0);
    else if (data == 'J' || data == 'j') motor(-1, 0);
    else if (data == 'S') motor(0, 0);
    else if (data >= '0' && data <= '9') {
      int pos = ('9' - data) * 20;
      head.write(pos);
    }
  }
}