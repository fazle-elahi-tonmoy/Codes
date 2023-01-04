void stat(byte a) {
  switch (a) {
    case 1:
      if (servo1_act[0]) for (byte i = 0; i < 8; i++) matrix[i] = right_arrow[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = left_arrow[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
    case 2:
      if (servo1_act[0]) for (byte i = 0; i < 8; i++) matrix[i] = right_stop[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = left_stop[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
    case 3:
      if (servo1_act[0]) for (byte i = 0; i < 8; i++) matrix[i] = left_arrow[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = right_arrow[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
    case 8:
    case 4:
      lc.clearDisplay(0); lc.clearDisplay(1);
      lc.setRow(0, 3, 0xFF); lc.setRow(0, 4, 0xFF);
      lc.setRow(1, 3, 0xFF); lc.setRow(1, 4, 0xFF);
      break;
    case 5:
      if (servo1_act[1]) for (byte i = 0; i < 8; i++) matrix[i] = right_arrow[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = left_arrow[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
    case 6:
      if (servo1_act[1]) for (byte i = 0; i < 8; i++) matrix[i] = right_stop[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = left_stop[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
    case 7:
      if (servo1_act[1]) for (byte i = 0; i < 8; i++) matrix[i] = left_arrow[i];
      else for (byte i = 0; i < 8; i++) matrix[i] = right_arrow[i];
      for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
      for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
      break;
  }
}
