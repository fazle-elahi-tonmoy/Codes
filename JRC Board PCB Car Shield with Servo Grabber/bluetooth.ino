void bluetooth() {
  int s = 10, spdl = 25, spdr = 25;
  int rise_state = 0;
  uint32_t t = millis();
  int lift_pos = rise;
  while (1) {
    if (SerialBT.available()) {
      char x = SerialBT.read();
      Serial.println(x);
      if (x == 'F') motor(s * spdl, s * spdr);
      else if (x == 'B') motor(-s * spdl, -s * spdr);
      else if (x == 'L') motor(-s * spdl, s * spdr);
      else if (x == 'R') motor(s * spdl, -s * spdr);
      else if (x == 'G') motor(0, s * spdr);
      else if (x == 'I') motor(s * spdl, 0);
      else if (x == 'J') motor(0, -s * spdr);
      else if (x == 'H') motor(-s * spdl, 0);
      else if (x == 'S') motor(0, 0);
      else if (x == 'W') light(1);
      else if (x == 'w') light(0);
      else if (x >= '0' && x <= '9') s = x - '0';
      else if (x == 'q') s = 10;
      else if (x >= 'k' && x <= 't') {
        byte p = x - 'k';
        int pos = map(p, 0, 9, dropl, grabl);
        handl.write(pos);
        pos = map(p, 0, 9, dropr, grabr);
        handr.write(pos);
      }
      else if (x == 'T') rise_state = 1;
      else if (x == 'D') rise_state = -1;
      else if (x == 'N') rise_state = 0;
    }

    
    if (rise_state == 1 && millis() - t > 10 && lift_pos < rise) {
      t = millis();
      lift_pos++;
      lift.write(lift_pos);
    }

    else if (rise_state == -1 && millis() - t > 10 && lift_pos > lower) {
      t = millis();
      lift_pos--;
      lift.write(lift_pos);
    }

    else rise_state == 0;
  }
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
}
