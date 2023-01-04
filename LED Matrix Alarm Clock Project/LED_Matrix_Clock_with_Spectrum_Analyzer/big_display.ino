void big_display(int a) {
  byte ONE[7]   = {0x20, 0x60, 0xa0, 0x20, 0x20, 0x20, 0xf8};
  byte TWO[7]   = {0xf8, 0x08, 0x08, 0xf8, 0x80, 0x80, 0xf8};
  byte THREE[7] = {0xf8, 0x08, 0x08, 0xf8, 0x08, 0x08, 0xf8};
  byte FOUR[7]  = {0x88, 0x88, 0x88, 0xf8, 0x08, 0x08, 0x08};
  byte FIVE[7]  = {0xf8, 0x80, 0x80, 0xf8, 0x08, 0x08, 0xf8};
  byte SIX[7]   = {0xf8, 0x80, 0x80, 0xf8, 0x88, 0x88, 0xf8};
  byte SEVEN[7] = {0xf8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};
  byte EIGHT[7] = {0xf8, 0x88, 0x88, 0xf8, 0x88, 0x88, 0xf8};
  byte NINE[7]  = {0xf8, 0x88, 0x88, 0xf8, 0x08, 0x08, 0xf8};
  byte ZERO[7]  = {0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf8};

  if (a / 100 >= 12) for (byte i = 0; i < 3; i++) matrix[i] |= 0x80;
  if (a / 100 > 12) a -= 1200;
  else if (a / 100 == 0) a += 1200;
  
  switch (a / 1000) {
    case 0: for (byte i = 0; i < 7; i++) matrix[i] |= ZERO[i] >> 2; break;
    case 1: for (byte i = 0; i < 7; i++) matrix[i] |= ONE[i] >> 2; break;
    case 2: for (byte i = 0; i < 7; i++) matrix[i] |= TWO[i] >> 2; break;
    case 3: for (byte i = 0; i < 7; i++) matrix[i] |= THREE[i] >> 2; break;
    case 4: for (byte i = 0; i < 7; i++) matrix[i] |= FOUR[i] >> 2; break;
    case 5: for (byte i = 0; i < 7; i++) matrix[i] |= FIVE[i] >> 2; break;
    case 6: for (byte i = 0; i < 7; i++) matrix[i] |= SIX[i] >> 2; break;
    case 7: for (byte i = 0; i < 7; i++) matrix[i] |= SEVEN[i] >> 2; break;
    case 8: for (byte i = 0; i < 7; i++) matrix[i] |= EIGHT[i] >> 2; break;
    case 9: for (byte i = 0; i < 7; i++) matrix[i] |= NINE[i] >> 2; break;
  }
  for (byte i = 0; i < 7; i++) lc.setRow(3, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;

  switch ((a % 1000) / 100) {
    case 0: for (byte i = 0; i < 7; i++) matrix[i] |= ZERO[i] >> 1; break;
    case 1: for (byte i = 0; i < 7; i++) matrix[i] |= ONE[i] >> 1; break;
    case 2: for (byte i = 0; i < 7; i++) matrix[i] |= TWO[i] >> 1; break;
    case 3: for (byte i = 0; i < 7; i++) matrix[i] |= THREE[i] >> 1; break;
    case 4: for (byte i = 0; i < 7; i++) matrix[i] |= FOUR[i] >> 1; break;
    case 5: for (byte i = 0; i < 7; i++) matrix[i] |= FIVE[i] >> 1; break;
    case 6: for (byte i = 0; i < 7; i++) matrix[i] |= SIX[i] >> 1; break;
    case 7: for (byte i = 0; i < 7; i++) matrix[i] |= SEVEN[i] >> 1; break;
    case 8: for (byte i = 0; i < 7; i++) matrix[i] |= EIGHT[i] >> 1; break;
    case 9: for (byte i = 0; i < 7; i++) matrix[i] |= NINE[i] >> 1; break;
  }
  if (menu_count == 1 && ss % 2) {
    matrix[1] |= 1; matrix[2] |= 1; matrix[5] |= 1; matrix[6] |= 1;
  }
  for (byte i = 0; i < 7; i++) lc.setRow(2, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;


  switch ((a % 100) / 10) {
    case 0: for (byte i = 0; i < 7; i++) matrix[i] |= ZERO[i] >> 2; break;
    case 1: for (byte i = 0; i < 7; i++) matrix[i] |= ONE[i] >> 2; break;
    case 2: for (byte i = 0; i < 7; i++) matrix[i] |= TWO[i] >> 2; break;
    case 3: for (byte i = 0; i < 7; i++) matrix[i] |= THREE[i] >> 2; break;
    case 4: for (byte i = 0; i < 7; i++) matrix[i] |= FOUR[i] >> 2; break;
    case 5: for (byte i = 0; i < 7; i++) matrix[i] |= FIVE[i] >> 2; break;
    case 6: for (byte i = 0; i < 7; i++) matrix[i] |= SIX[i] >> 2; break;
    case 7: for (byte i = 0; i < 7; i++) matrix[i] |= SEVEN[i] >> 2; break;
    case 8: for (byte i = 0; i < 7; i++) matrix[i] |= EIGHT[i] >> 2; break;
    case 9: for (byte i = 0; i < 7; i++) matrix[i] |= NINE[i] >> 2; break;
  }
  if (menu_count == 1 && ss % 2) {
    matrix[1] |= 0x80; matrix[2] |= 0x80; matrix[5] |= 0x80; matrix[6] |= 0x80;
  }
  
  for (byte i = 0; i < 7; i++) lc.setRow(1, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;

  switch (a % 10) {
    case 0: for (byte i = 0; i < 7; i++) matrix[i] |= ZERO[i] >> 1; break;
    case 1: for (byte i = 0; i < 7; i++) matrix[i] |= ONE[i] >> 1; break;
    case 2: for (byte i = 0; i < 7; i++) matrix[i] |= TWO[i] >> 1; break;
    case 3: for (byte i = 0; i < 7; i++) matrix[i] |= THREE[i] >> 1; break;
    case 4: for (byte i = 0; i < 7; i++) matrix[i] |= FOUR[i] >> 1; break;
    case 5: for (byte i = 0; i < 7; i++) matrix[i] |= FIVE[i] >> 1; break;
    case 6: for (byte i = 0; i < 7; i++) matrix[i] |= SIX[i] >> 1; break;
    case 7: for (byte i = 0; i < 7; i++) matrix[i] |= SEVEN[i] >> 1; break;
    case 8: for (byte i = 0; i < 7; i++) matrix[i] |= EIGHT[i] >> 1; break;
    case 9: for (byte i = 0; i < 7; i++) matrix[i] |= NINE[i] >> 1; break;
  }
  
  if (clock.isArmed1() && menu_count != 3)
    for (byte i = 0; i < 3; i++) matrix[i] |= 1;
    
  for (byte i = 0; i < 7; i++) lc.setRow(0, i, matrix[i]);
  for (byte i = 0; i < 8; i++) matrix[i] = 0;
}
