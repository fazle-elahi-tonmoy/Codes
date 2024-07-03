void remote_control() {
  byte spd = 9;
  int rise_state = 0;
  uint32_t t = millis();
  int lift_pos = rise;

  while (1) {
    press();
    if (SerialBT.available() > 0) {
      char data = SerialBT.read();
      Serial.println(data);
      if (data == 'F') motor(3, 3);
      else if (data == 'B') motor(-3, -3);
      else if (data == 'L') motor(-3, 3);
      else if (data == 'R') motor(3, -3);
      else if (data == 'G') motor(0, 3);
      else if (data == 'H') motor(0, -3);
      else if (data == 'I') motor(3, 0);
      else if (data == 'J') motor(-3, 0);
      else if (data == 'g') motor(2, 3);
      else if (data == 'h') motor(-1, -3);
      else if (data == 'i') motor(3, 2);
      else if (data == 'j') motor(-3, -1);
      else if (data >= 'k' && data <= 't') {
        byte x = 9 - (data - 'k');
        x = map(x, 0, 9, 20, drop);
        hand.write(x);
      }

      else if (data >= '0' && data <= '9') {
        spd = data - '0';
        ledcWrite(2, spd * 28);
      }

      else if (data == 'T') rise_state = 1;
      else if (data == 'D') rise_state = -1;
      else if (data == 'N') rise_state = 0;
      else if (data == 'W') lift.write(lower);
      else if (data == 'w') lift.write(mrise);
      else if (data == 'X') hand.write(grab);
      else if (data == 'x') hand.write(drop);
      else if (data == 'S') motor(0, 0);
    }

    if (rise_state == 1 && millis() - t > 10 && lift_pos > rise) {
      t = millis();
      lift_pos--;
      lift.write(lift_pos);
    }

    else if (rise_state == -1 && millis() - t > 10 && lift_pos < lower) {
      t = millis();
      lift_pos++;
      lift.write(lift_pos);
    }

    else rise_state == 0;
  }
}
