void remote_control() {
  byte spd = 10;
  while (1) {
    if (SerialBT.available() > 0) {
      char data = SerialBT.read();
      Serial.println(data);
      if (data == 'F') motor(25 * spd, 25 * spd);
      else if (data == 'B') motor(-25 * spd, -25 * spd);
      else if (data == 'L') motor(-25 * spd, 25 * spd);
      else if (data == 'R') motor(25 * spd, -25 * spd);
      else if (data == 'G' || data == 'g') motor(0, 25 * spd);
      else if (data == 'H' || data == 'h') motor(0, -25 * spd);
      else if (data == 'I' || data == 'i') motor(25 * spd, 0);
      else if (data == 'J' || data == 'j') motor(-25 * spd, 0);
      else if (data >= '0' && data <= '9') spd = data - '0' + 1;
      else if (data == 'S') motor(0, 0);
    }
  }
}
