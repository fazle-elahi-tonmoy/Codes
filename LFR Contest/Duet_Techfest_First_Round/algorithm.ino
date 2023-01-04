void algorithm() {
  int s = 0, a = 0;
  if (side == 2)
    for (int i = 0;; i++) {
      if (scan[i] == 1) scan[i] = 3;
      else if (scan[i] == 3) scan[i] = 1;
      else if (scan[i] == 5) break;
    }
  while (1) {
    if (scan[a + 1] == 4) {
      a += 2; scan[s] = scan[s] + scan[a];
    }
    if (scan[s] == 4) {
      s--; a++; scan[s] = scan[s] + scan[a];
    }
    else {
      s++; a++; scan[s] = scan[a];
    }
    if (scan[s] == 5) break;
  }
  if (side == 2)
    for (int i = 0;; i++) {
      if (scan[i] == 1) scan[i] = 3;
      else if (scan[i] == 3) scan[i] = 1;
      else if (scan[i] == 5) break;
    }
  EEPROM.write(19, s);
  for (int i = 0; i <= s ; i++) {
    EEPROM.write(i + 20, scan[i]); delay(10);
  }
}
