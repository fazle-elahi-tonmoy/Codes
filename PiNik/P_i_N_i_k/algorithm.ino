void algorithm() {
  byte s = 0;
  byte a = 0;
  a = EEPROM.read(6);
  side = EEPROM.read(9) / 100;
  if (side == 2) {
    while (scan[a] != 0) {
      if (scan[a] == 1) scan[a] = 3;
      else if (scan[a] == 3) scan[a] = 1;
      a++;
    }
  }

  s = a = EEPROM.read(6);
  while (scan[s] != 0) {
    if (scan[a + 1] == 4) {
      a += 2;
      scan[s] = scan[s] + scan[a];
    }
    if (scan[s] == 4) {
      s--; a++;
      scan[s] = scan[s] + scan[a];
    }
    else {
      s++; a++;
      scan[s] = scan[a];
    }
  }

  a = EEPROM.read(6);
  if (side == 2) {
    while (scan[a] != 0) {
      if (scan[a] == 1) scan[a] = 3;
      else if (scan[a] == 3) scan[a] = 1;
      a++;
    }
  }

  a = EEPROM.read(6);
  while (1) {
    EEPROM.write(a + m_base, scan[a]); delay(10);
    if (scan[a] == 0) break; a++;
  }
}
