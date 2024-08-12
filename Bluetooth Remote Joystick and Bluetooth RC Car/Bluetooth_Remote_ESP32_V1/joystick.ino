void joystick() {
  for (byte i = 0; i < 8; i++) button_val[i] = digitalRead(button[i]);
  for (byte i = 0; i < 4; i++) {
    pot_val[i] = analogRead(pot[i]);
    if (pot_val[i] < pot_mid[i] - 1000) pot_val[i] = -1;
    else if (pot_val[i] > pot_mid[i] + 1000) pot_val[i] = 1;
    else pot_val[i] = 0;
  }
}

int recheck() {
  bool state[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int base[13] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };
  long result = 0;
  joystick();
  for (byte i = 0; i < 8; i++) {
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