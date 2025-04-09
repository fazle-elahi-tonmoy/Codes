void saveStringToEEPROM(int address, String data) {
  int length = data.length();
  for (int i = 0; i < length; i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.commit();
}

