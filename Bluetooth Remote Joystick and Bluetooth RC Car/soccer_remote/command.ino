void command() {
  if (l1 == 1) {
    if (tmp != 'G') {
      tmp = 'G';
      Serial.write('y');
    }
  }
  else if (l2 == 1) {
    if (tmp != 'H') {
      tmp = 'H';
      Serial.write('z');
    }
  }
  else if (r1 == 1) {
    if (tmp != 'I') {
      tmp = 'I';
      Serial.write('w');
    }
  }
  else if (r2 == 1) {
    if (tmp != 'J') {
      tmp = 'J';
      Serial.write('x');
    }
  }
  else if (rx <= 450) {
    tmp = 'L';
    Serial.write('l');
  }
  else if (rx >= 600) {
    if (tmp != 'R') {
      tmp = 'R';
      Serial.write('r');
    }
  }
  else if (ly <= 450) {
    if (tmp != 'F') {
      tmp = 'F';
      Serial.write('f');
    }
  }
  else if (ly >= 600) {
    if (tmp != 'B') {
      tmp = 'B';
      Serial.write('b');
    }
  }

  else {
    if (tmp != 'S') {
      tmp = 'S';
      Serial.write('s');
    }
  }


}//END OF COMMAND
