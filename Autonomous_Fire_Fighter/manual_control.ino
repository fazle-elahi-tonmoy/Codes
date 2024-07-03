void remote_control() {
  SerialBT.begin("Fire Fighter");
  byte spd = 10;
  byte pos = 5;
  servo.write(180 - pos * 20);
  while (1) {
    if (SerialBT.available() > 0) {
      char data = SerialBT.read();
      Serial.println(data);
      if (data == 'F') motor(25 * spd, 25 * spd);
      else if (data == 'B') motor(-25 * spd, -25 * spd);
      else if (data == 'L') motor(-25 * spd, 25 * spd);
      else if (data == 'R') motor(25 * spd, -25 * spd);
      else if (data == 'I') motor(25 * spd, 0);
      else if (data == 'G') motor(0, 25 * spd);
      else if (data == 'J') motor(-25 * spd, 0);
      else if (data == 'H') motor(0, -25 * spd);
      else if (data == 'W') digitalWrite(relay, HIGH);
      else if (data == 'w') digitalWrite(relay, LOW);
      else if (data >= '1' && data <= '8') {
        pos = data - '0';
        Serial.println(pos * 20);
        servo.write(180 - pos * 20);
      }

      else if (data == 'S') motor(0, 0);
    }
  }
}
