void saveStringToEEPROM(int address, const String& data) {
  int length = data.length();
  for (int i = 0; i < length; i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + length, '\0');
  EEPROM.commit();
}

void readStringFromEEPROM(int address) {
  int i = 0;
  while (i < 14) {
    phone_number[i] = EEPROM.read(address+i);
    i++;
  }
}