void temp_value(int a) {
  switch (a / 10) {
    case 0: for (byte i = 2; i < 7; i++) matrix[i] |= zero[i - 2]; break;
    case 1: for (byte i = 2; i < 7; i++) matrix[i] |= one[i - 2]; break;
    case 2: for (byte i = 2; i < 7; i++) matrix[i] |= two[i - 2]; break;
    case 3: for (byte i = 2; i < 7; i++) matrix[i] |= three[i - 2]; break;
    case 4: for (byte i = 2; i < 7; i++) matrix[i] |= four[i - 2]; break;
    case 5: for (byte i = 2; i < 7; i++) matrix[i] |= five[i - 2]; break;
    case 6: for (byte i = 2; i < 7; i++) matrix[i] |= six[i - 2]; break;
    case 7: for (byte i = 2; i < 7; i++) matrix[i] |= seven[i - 2]; break;
    case 8: for (byte i = 2; i < 7; i++) matrix[i] |= eight[i - 2]; break;
    case 9: for (byte i = 2; i < 7; i++) matrix[i] |= nine[i - 2]; break;
  }

  switch (a % 10) {
    case 0: for (byte i = 2; i < 7; i++) matrix[i] |= zero[i - 2] >> 4; break;
    case 1: for (byte i = 2; i < 7; i++) matrix[i] |= one[i - 2] >> 4; break;
    case 2: for (byte i = 2; i < 7; i++) matrix[i] |= two[i - 2] >> 4; break;
    case 3: for (byte i = 2; i < 7; i++) matrix[i] |= three[i - 2] >> 4; break;
    case 4: for (byte i = 2; i < 7; i++) matrix[i] |= four[i - 2] >> 4; break;
    case 5: for (byte i = 2; i < 7; i++) matrix[i] |= five[i - 2] >> 4; break;
    case 6: for (byte i = 2; i < 7; i++) matrix[i] |= six[i - 2] >> 4; break;
    case 7: for (byte i = 2; i < 7; i++) matrix[i] |= seven[i - 2] >> 4; break;
    case 8: for (byte i = 2; i < 7; i++) matrix[i] |= eight[i - 2] >> 4; break;
    case 9: for (byte i = 2; i < 7; i++) matrix[i] |= nine[i - 2] >> 4; break;
  }
  for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;
  
  if (menu_count == 6) for (byte i = 0; i < 8; i++) matrix[i] = farenhite[i];
  else if (menu_count == 7) for (byte i = 0; i < 8; i++) matrix[i] = celcius[i];
  else if (menu_count == 8) for (byte i = 0; i < 8; i++) matrix[i] = percentage[i];
  for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;

}
