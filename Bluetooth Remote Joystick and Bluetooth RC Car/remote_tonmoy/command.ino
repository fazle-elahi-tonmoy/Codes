void command() {
  if (l1 == 1) {
    if (tmp != 'G') {
      tmp = 'G';
      (mode == 0) ? Serial.write(tmp) : Serial.write('y');
    }
  }
  else if (l2 == 1) {
    if (tmp != 'H') {
      tmp = 'H';
      (mode == 0) ? Serial.write(tmp) : Serial.write('z');
    }
  }
  else if (r1 == 1) {
    if (tmp != 'I') {
      tmp = 'I';
      (mode == 0) ? Serial.write(tmp) : Serial.write('w');
    }
  }
  else if (r2 == 1) {
    if (tmp != 'J') {
      tmp = 'J';
      (mode == 0) ? Serial.write(tmp) : Serial.write('x');
    }
  }
  else if (ly <= 450 && rx >= 450 && rx <= 600) {
    if (tmp != 'F') {
      tmp = 'F';
      (mode == 0) ? Serial.write(tmp) : Serial.write('f');
    }
  }
  else if (ly >= 600 && rx >= 450 && rx <= 600) {
    if (tmp != 'B') {
      tmp = 'B';
      (mode == 0) ? Serial.write(tmp) : Serial.write('b');
    }
  }
  else if (rx <= 450 && ly >= 450 && ly <= 600) {
    if (tmp != 'L') {
      tmp = 'L';
      (mode == 0) ? Serial.write(tmp) : Serial.write('l');
    }
  }
  else if (rx >= 600 && ly >= 450 && ly <= 600) {
    if (tmp != 'R') {
      tmp = 'R';
      (mode == 0) ? Serial.write(tmp) : Serial.write('r');
    }
  }
  else if (ly <= 450 && rx <= 450) {
    if (tmp != 'G') {
      tmp = 'G';
      (mode == 0) ? Serial.write(tmp) : Serial.write('l');
    }
  }
  else if (ly <= 450 && rx >= 600) {
    if (tmp != 'I') {
      tmp = 'I';
      (mode == 0) ? Serial.write(tmp) : Serial.write('r');
    }
  }
  else if (ly >= 600 && rx <= 450) {
    if (tmp != 'H') {
      tmp = 'H';
      (mode == 0) ? Serial.write(tmp) : Serial.write('l');
    }
  }
  else if (ly >= 600 && rx >= 600) {
    if (tmp != 'J') {
      tmp = 'J';
     (mode == 0) ? Serial.write(tmp) : Serial.write('r');
    }
  }
  else if (l1 == 1 && r1 == 1) {
    if (tmp != 'F') {
      tmp = 'F';
      (mode == 0) ? Serial.write(tmp) : Serial.write('f');
    }
  }
  else if (l1 == 1 && r2 == 1) {
    if (tmp != 'L') {
      tmp = 'L';
      (mode == 0) ? Serial.write(tmp) : Serial.write('l');
    }
  }
  else if (l2 == 1 && r2 == 1) {
    if (tmp != 'B') {
      tmp = 'B';
      (mode == 0) ? Serial.write(tmp) : Serial.write('b');
    }
  }
  else if (l2 == 1 && r1 == 1) {
    if (tmp != 'R') {
      tmp = 'R';
      (mode == 0) ? Serial.write(tmp) : Serial.write('r');
    }
  }
  else if (lmb == 1) {
    mode = 0;
    digitalWrite(13, LOW);
  }
  else if (rmb == 1) {
    mode = 1;
    digitalWrite(13, HIGH);
  }
  else {
    if (tmp != 'S') {
      tmp = 'S';
      (mode == 0) ? Serial.write(tmp) : Serial.write('s');
    }
  }

  if (tmpl != pl && mode == 0) {
    tmpl = pl;
    if (pl == 0) Serial.write('0');
    else if (pl == 1) Serial.write('1');
    else if (pl == 2) Serial.write('2');
    else if (pl == 3) Serial.write('3');
    else if (pl == 4) Serial.write('4');
    else if (pl == 5) Serial.write('5');
    else if (pl == 6) Serial.write('6');
    else if (pl == 7) Serial.write('7');
    else if (pl == 8) Serial.write('8');
    else if (pl == 9) Serial.write('9');
  }

  if (tmpr != pr && mode == 0) {
    tmpr = pr;
    if (pr == 0) Serial.write('a');
    else if (pr == 1) Serial.write('b');
    else if (pr == 2) Serial.write('c');
    else if (pr == 3) Serial.write('d');
    else if (pr == 4) Serial.write('e');
    else if (pr == 5) Serial.write('f');
    else if (pr == 6) Serial.write('g');
    else if (pr == 7) Serial.write('h');
    else if (pr == 8) Serial.write('i');
    else if (pr == 9) Serial.write('j');
  }

}//END OF COMMAND
