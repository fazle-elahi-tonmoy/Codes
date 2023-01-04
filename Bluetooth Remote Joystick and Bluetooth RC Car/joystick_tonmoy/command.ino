void command() {
  if (l1 == 1) Serial.write('G');
  else if (l2 == 1) Serial.write('H');
  else if (r1 == 1) Serial.write('I');
  else if (r2 == 1) Serial.write('J');
  else if (ly <= 450 && rx >= 450 && rx <= 600) Serial.write('F');
  else if (ly >= 600 && rx >= 450 && rx <= 600) Serial.write('B');
  else if (rx <= 450 && ly >= 450 && ly <= 600) Serial.write('L');
  else if (rx >= 600 && ly >= 450 && ly <= 600) Serial.write('R');
  else if (ly <= 450 && rx <= 450) Serial.write('L'); //real command G
  else if (ly <= 450 && rx >= 600) Serial.write('R');  //real command I
  else if (ly >= 600 && rx <= 450) Serial.write('L'); //real command H
  else if (ly >= 600 && rx >= 600) Serial.write('R'); //real command J
  //  else if (l1 == 1 && r1 == 1) Serial.write('F');
  //  else if (l1 == 1 && r2 == 1) Serial.write('L');
  //  else if (l2 == 1 && r2 == 1) Serial.write('B');
  //  else if (l2 == 1 && r1 == 1) Serial.write('R');
  //  else if (lmb == 1 && tmp != 'W') Serial.write('W');
  //  else if (rmb == 1 && tmp != 'U') Serial.write('U');
  //  else if (lmb == 1) {
  //    if (i == 0) {
  //      Serial.write('W');
  //      i = 1;
  //    }
  //    else {
  //      Serial.write('w');
  //      i = 0;
  //    }
  //    delay(500);
  //  }
  //
  //  else if (rmb == 1) {
  //    if (j == 0) {
  //      Serial.write('U');
  //      j = 1;
  //    }
  //    else {
  //      Serial.write('u');
  //      j = 0;
  //    }
  //    delay(500);
  //  }
  else if (tmp != 'S') Serial.write('S');

  //  if (tmpl != pl) {
  //    tmpl = pl;
  //    if (pl == 0) Serial.write('0');
  //    else if (pl == 1) Serial.write('1');
  //    else if (pl == 2) Serial.write('2');
  //    else if (pl == 3) Serial.write('3');
  //    else if (pl == 4) Serial.write('4');
  //    else if (pl == 5) Serial.write('5');
  //    else if (pl == 6) Serial.write('6');
  //    else if (pl == 7) Serial.write('7');
  //    else if (pl == 8) Serial.write('8');
  //    else if (pl == 9) Serial.write('9');
  //  }
  //  if (tmpr != pr) {
  //    tmpr = pr;
  //    if (pr == 0) Serial.write('a');
  //    else if (pr == 1) Serial.write('b');
  //    else if (pr == 2) Serial.write('c');
  //    else if (pr == 3) Serial.write('d');
  //    else if (pr == 4) Serial.write('e');
  //    else if (pr == 5) Serial.write('f');
  //    else if (pr == 6) Serial.write('g');
  //    else if (pr == 7) Serial.write('h');
  //    else if (pr == 8) Serial.write('i');
  //    else if (pr == 9) Serial.write('j');
  //  }
}
