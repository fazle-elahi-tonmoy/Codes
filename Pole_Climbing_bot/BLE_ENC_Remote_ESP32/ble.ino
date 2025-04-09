void ble_joystick() {
  if (!ble_connection) bleKeyboard.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.drawBitmap(4, 16, gamepad_icon, 24, 24, 1);
  text("  BLE  ", 44, 12);
  text("CONTROL", 44, 36);
  display.display();
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? display.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : display.drawBitmap(119, 0, no_connection, 8, 8, 0);
      display.display();
    }

    if (ble_connection) {
      int p = recheck();
      if (p < 4 && p > 0) {
        if (joystick[1] == 1) bleKeyboard.press(KEY_UP_ARROW);
        else if (joystick[1] == -1) bleKeyboard.press(KEY_DOWN_ARROW);
        else {
          bleKeyboard.release(KEY_UP_ARROW);
          bleKeyboard.release(KEY_DOWN_ARROW);
        }
      }
      if (p >= 4 && p <= 8) {
        if (joystick[2] == 1) bleKeyboard.press(KEY_LEFT_ARROW);
        else if (joystick[2] == -1) bleKeyboard.press(KEY_RIGHT_ARROW);
        else {
          bleKeyboard.release(KEY_LEFT_ARROW);
          bleKeyboard.release(KEY_RIGHT_ARROW);
        }
      }
      if (p > 8) {
        if (!button_val[0] && !button_val[1]) break;
        (!button_val[0]) ? bleKeyboard.press(KEY_ESC) : bleKeyboard.release(KEY_ESC);
        (!button_val[1]) ? bleKeyboard.press(KEY_RETURN) : bleKeyboard.release(KEY_RETURN);
        (!button_val[2]) ? bleKeyboard.press(KEY_RIGHT_CTRL) : bleKeyboard.release(KEY_RIGHT_CTRL);
        (!button_val[3]) ? bleKeyboard.press(KEY_RIGHT_SHIFT) : bleKeyboard.release(KEY_RIGHT_SHIFT);
        (!button_val[4]) ? bleKeyboard.press(KEY_MEDIA_MUTE) : bleKeyboard.release(KEY_MEDIA_MUTE);
        (!button_val[5]) ? bleKeyboard.press(KEY_MEDIA_PLAY_PAUSE) : bleKeyboard.release(KEY_RETURN);
      }


      byte r = Rencoder_read();
      if (r) {
        (r == 1) ? bleKeyboard.write(KEY_MEDIA_VOLUME_UP) : bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      }
      byte l = Lencoder_read();
      if (l) {
        (l == 1) ? bleKeyboard.write(KEY_PAGE_UP) : bleKeyboard.write(KEY_PAGE_DOWN);
      }
    }
  }
  bleKeyboard.releaseAll();
  // bleKeyboard.end();
  // ble_connection = 0;
}