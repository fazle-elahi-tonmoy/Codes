void algorithm() {
  int s = 0, a = 0;
  if (side == 2) conversion();
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
  if (side == 2) conversion();
}

void conversion() {
  for (int i = 0;; i++) {
    if (scan[i] == 1) scan[i] = 3;
    else if (scan[i] == 3) scan[i] = 1;
    else if (scan[i] == 5) break;
  }
}

void memory_save() {
  counter = 0;
  while (1) {
    EEPROM.update(scan_start + counter, scan[counter]);
    delay(1);
    if (scan[counter] == 5 || counter == 50) break;
    counter++;
  }
}

void memory_recall() {
  for (int i = scan_start; i < scan_start + 50 ; i++) {
    scan[i - scan_start] = EEPROM.read(i);
    Serial.print(scan[i - scan_start]);
    Serial.print(" ");
    if (scan[i - scan_start] == 5) break;
  }
}
