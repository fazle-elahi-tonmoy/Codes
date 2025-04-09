void saveStringToEEPROM(int address, const String& data) {
  int len = data.length();
  for (int i = 0; i < len; i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + len, '\0');
  EEPROM.commit();
}

String readStringFromEEPROM(int address) {
  String data = "";
  char ch;
  for (int i = 0; i < 10; i++) {
    ch = EEPROM.read(address + i);
    if (ch == '\0') {
      break;
    }
    data += ch;
  }
  return data;
}

char* readCharFromEEPROM(int address) {
  int len = 0;
  while (EEPROM.read(address + len) != '\0') {
    len++;
  }

  char* buffer = new char[len + 1];
  for (int i = 0; i <= len; i++) {
    buffer[i] = EEPROM.read(address + i);
  }

  return buffer;
}