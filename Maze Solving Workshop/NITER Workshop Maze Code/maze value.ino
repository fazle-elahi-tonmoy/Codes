void memory_save() {
  byte i = 0;
  while (1) {
    EEPROM.write(i + 100, path[i]);
    delay(10);
    if (path[i] == 5) break;
    i++;
  }
}

void memory_recall() {
  byte i = 0;
  while (1) {
    path[i] = EEPROM.read(i + 100);
    i++;
    if (path[i] == 5) break;
  }
}

byte solving_pattern() {
  byte i = 0;
  while (1) {
    if(path[i] == 1) path[i] == 3;
    else if(path[i] == 3) path[i] == 1;
    if (path[i] == 5) break;
    i++;
  }
  return i-1;
}

void memory_clear() {
  byte i = 0;
  while (i < 50) {
    EEPROM.write(i + 100, 0);
    delay(10);
    i++;
  }
}