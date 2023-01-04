void stat(byte a) {
  switch (a) {
    case 1:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x80);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x80);
      break;
    case 2:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x20);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x20);
      break;
    case 3:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x01);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x01);
      break;
    case 4:
      lc.clearDisplay(0); lc.clearDisplay(1);
      lc.setRow(0, 3, 0xFF); lc.setRow(0, 4, 0xFF);
      lc.setRow(1, 3, 0xFF); lc.setRow(1, 4, 0xFF);
      break;
    case 5:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x01);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x01);
      break;
    case 6:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x04);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x04);
      break;
    case 7:
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, 0x80);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, 0x80);
      break;
  }
}
