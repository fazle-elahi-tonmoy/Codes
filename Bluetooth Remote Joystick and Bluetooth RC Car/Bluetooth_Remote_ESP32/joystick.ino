void joystick() {
  for (byte i = 0; i < 6; i++) button_val[i] = digitalRead(button[i]);
  for (byte i = 0; i < 4; i++) {
    pot_val[i] = analogRead(pot[i]);
    if (pot_val[i] < pot_mid[i] - 1000) pot_val[i] = -1;
    else if (pot_val[i] > pot_mid[i] + 1000) pot_val[i] = 1;
    else pot_val[i] = 0;
  }
  // pot_val[4] = map(pot_val[4], pot_min[0], pot_max[0], 0, 9);
  // pot_val[5] = map(pot_val[5], pot_min[1], pot_max[1], 0, 9);
  pot_map(0);
  pot_map(1);
}

int recheck() {
  bool state[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int base[12] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
  int result = 0;
  joystick();
  for (byte i = 0; i < 6; i++) {
    if (temp[i] != button_val[i]) {
      state[i] = 1;
      temp[i] = button_val[i];
    }
    result += state[i] * base[11 - i];
  }

  for (byte i = 0; i < 6; i++) {
    if (temp[i + 6] != pot_val[i]) {
      state[i + 6] = 1;
      temp[i + 6] = pot_val[i];
    }
    result += state[i + 6] * base[5 - i];
  }

  return result;
}

void pot_map(byte a) {
  int t = pot_val[a + 4];
  pot_val[a + 4] = analogRead(pot[a + 4]);
  bool flag = 0;
  for (int i = 0; i <= 9; i++) {
    if (pot_val[a + 4] >= (i * 415) && pot_val[a + 4] <= ((i + 1) * 415 - 100)) {
      pot_val[a + 4] = i;
      flag = 1;
      break;
    }
  }

  if (!flag) pot_val[a + 4] = t;
}