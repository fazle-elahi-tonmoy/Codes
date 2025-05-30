void input_read() {
  for (byte i = 0; i < 6; i++) button_val[i] = digitalRead(button[i]);
  for (byte i = 0; i < 4; i++) {
    joystick[i] = analogRead(joystick_pin[i]);
    if (i == 2 || i == 3) {
      if (joystick[i] < joy_mid[i] - 1000) joystick[i] = -1;
      else if (joystick[i] > joy_mid[i] + 1000) joystick[i] = 1;
      else joystick[i] = 0;
    } else {
      if (joystick[i] < joy_mid[i] - 1000) joystick[i] = 1;
      else if (joystick[i] > joy_mid[i] + 1000) joystick[i] = -1;
      else joystick[i] = 0;
    }
  }
}

int recheck() {
  bool state[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int base[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
  int result = 0;
  input_read();
  for (byte i = 0; i < 6; i++) {
    if (temp[i] != button_val[i]) {
      state[i] = 1;
      temp[i] = button_val[i];
    }
    result += state[i] * base[i + 4];
  }

  for (byte i = 0; i < 4; i++) {
    if (temp[i + 6] != joystick[i]) {
      state[i + 6] = 1;
      temp[i + 6] = joystick[i];
    }
    result += state[i + 6] * base[i];
  }
  return result;
}