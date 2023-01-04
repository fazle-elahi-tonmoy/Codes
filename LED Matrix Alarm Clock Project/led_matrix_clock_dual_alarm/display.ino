void display_value(int a) {
  byte one[5]   = {B01000000, B11000000, B01000000, B01000000, B11100000};
  byte two[5]   = {B11100000, B00100000, B11100000, B10000000, B11100000};
  byte three[5] = {B11100000, B00100000, B11100000, B00100000, B11100000};
  byte four[5]  = {B10100000, B10100000, B11100000, B00100000, B00100000};
  byte five[5]  = {B11100000, B10000000, B11100000, B00100000, B11100000};
  byte six[5]   = {B11100000, B10000000, B11100000, B10100000, B11100000};
  byte seven[5] = {B11100000, B00100000, B00100000, B00100000, B00100000};
  byte eight[5] = {B11100000, B10100000, B11100000, B10100000, B11100000};
  byte nine[5]  = {B11100000, B10100000, B11100000, B00100000, B11100000};
  byte zero[5]  = {B11100000, B10100000, B10100000, B10100000, B11100000};

  if (a / 100 >= 12) matrix[7] |= pm_symbol;
  if (a / 100 > 12) a -= 1200;
  else if (a / 100 == 0) a += 1200;
  if (ss % 2 && menu_count == 1) matrix[7] |= second_symbol_1;
  if(menu_count == 4) matrix[7] |= B00000001;

  switch (a / 1000) {
    case 0: for (byte i = 1; i < 6; i++) matrix[i] |= zero[i - 1]; break;
    case 1: for (byte i = 1; i < 6; i++) matrix[i] |= one[i - 1]; break;
    case 2: for (byte i = 1; i < 6; i++) matrix[i] |= two[i - 1]; break;
    case 3: for (byte i = 1; i < 6; i++) matrix[i] |= three[i - 1]; break;
    case 4: for (byte i = 1; i < 6; i++) matrix[i] |= four[i - 1]; break;
    case 5: for (byte i = 1; i < 6; i++) matrix[i] |= five[i - 1]; break;
    case 6: for (byte i = 1; i < 6; i++) matrix[i] |= six[i - 1]; break;
    case 7: for (byte i = 1; i < 6; i++) matrix[i] |= seven[i - 1]; break;
    case 8: for (byte i = 1; i < 6; i++) matrix[i] |= eight[i - 1]; break;
    case 9: for (byte i = 1; i < 6; i++) matrix[i] |= nine[i - 1]; break;
  }

  switch ((a % 1000) / 100) {
    case 0: for (byte i = 1; i < 6; i++) matrix[i] |= zero[i - 1] >> 4; break;
    case 1: for (byte i = 1; i < 6; i++) matrix[i] |= one[i - 1] >> 4; break;
    case 2: for (byte i = 1; i < 6; i++) matrix[i] |= two[i - 1] >> 4; break;
    case 3: for (byte i = 1; i < 6; i++) matrix[i] |= three[i - 1] >> 4; break;
    case 4: for (byte i = 1; i < 6; i++) matrix[i] |= four[i - 1] >> 4; break;
    case 5: for (byte i = 1; i < 6; i++) matrix[i] |= five[i - 1] >> 4; break;
    case 6: for (byte i = 1; i < 6; i++) matrix[i] |= six[i - 1] >> 4; break;
    case 7: for (byte i = 1; i < 6; i++) matrix[i] |= seven[i - 1] >> 4; break;
    case 8: for (byte i = 1; i < 6; i++) matrix[i] |= eight[i - 1] >> 4; break;
    case 9: for (byte i = 1; i < 6; i++) matrix[i] |= nine[i - 1] >> 4; break;
  }


  for (byte i = 0; i < 8; i++) lc.setRow(1, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;

  switch ((a % 100) / 10) {
    case 0: for (byte i = 1; i < 6; i++) matrix[i] |= zero[i - 1] >> 1; break;
    case 1: for (byte i = 1; i < 6; i++) matrix[i] |= one[i - 1] >> 1; break;
    case 2: for (byte i = 1; i < 6; i++) matrix[i] |= two[i - 1] >> 1; break;
    case 3: for (byte i = 1; i < 6; i++) matrix[i] |= three[i - 1] >> 1; break;
    case 4: for (byte i = 1; i < 6; i++) matrix[i] |= four[i - 1] >> 1; break;
    case 5: for (byte i = 1; i < 6; i++) matrix[i] |= five[i - 1] >> 1; break;
    case 6: for (byte i = 1; i < 6; i++) matrix[i] |= six[i - 1] >> 1; break;
    case 7: for (byte i = 1; i < 6; i++) matrix[i] |= seven[i - 1] >> 1; break;
    case 8: for (byte i = 1; i < 6; i++) matrix[i] |= eight[i - 1] >> 1; break;
    case 9: for (byte i = 1; i < 6; i++) matrix[i] |= nine[i - 1] >> 1; break;
  }

  switch (a % 10) {
    case 0: for (byte i = 1; i < 6; i++) matrix[i] |= zero[i - 1] >> 5; break;
    case 1: for (byte i = 1; i < 6; i++) matrix[i] |= one[i - 1] >> 5; break;
    case 2: for (byte i = 1; i < 6; i++) matrix[i] |= two[i - 1] >> 5; break;
    case 3: for (byte i = 1; i < 6; i++) matrix[i] |= three[i - 1] >> 5; break;
    case 4: for (byte i = 1; i < 6; i++) matrix[i] |= four[i - 1] >> 5; break;
    case 5: for (byte i = 1; i < 6; i++) matrix[i] |= five[i - 1] >> 5; break;
    case 6: for (byte i = 1; i < 6; i++) matrix[i] |= six[i - 1] >> 5; break;
    case 7: for (byte i = 1; i < 6; i++) matrix[i] |= seven[i - 1] >> 5; break;
    case 8: for (byte i = 1; i < 6; i++) matrix[i] |= eight[i - 1] >> 5; break;
    case 9: for (byte i = 1; i < 6; i++) matrix[i] |= nine[i - 1] >> 5; break;
  }

  if (ss % 2 && menu_count == 1) matrix[7] |= second_symbol_2;
  if(menu_count == 5) matrix[7] |= B10000000;
  if (clock.isArmed1()) matrix[7] |= alarm_symbol;
  if (clock.isArmed2()) matrix[7] |= special_alarm_symbol;
  for (byte i = 0; i < 8; i++) lc.setRow(0, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;

}
