void ble_joystick() {
  bool ble_connection = 0;
  bleKeyboard.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.drawBitmap(0, 4, gamepad_icon, 24, 24, 1);
  text("  BLE  ", 36, 0);
  text("CONTROL", 36, 16);
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
        if (joystick[0] == -1) bleKeyboard.press(KEY_UP_ARROW);
        else if (joystick[0] == 1) bleKeyboard.press(KEY_DOWN_ARROW);
        else {
          bleKeyboard.release(KEY_UP_ARROW);
          bleKeyboard.release(KEY_DOWN_ARROW);
        }
      }
      if (p >= 4 && p <= 8) {
        if (joystick[3] == -1) bleKeyboard.press(KEY_LEFT_ARROW);
        else if (joystick[3] == 1) bleKeyboard.press(KEY_RIGHT_ARROW);
        else {
          bleKeyboard.release(KEY_LEFT_ARROW);
          bleKeyboard.release(KEY_RIGHT_ARROW);
        }
      }
      if (p > 8) {
        (!button_val[2]) ? bleKeyboard.press(KEY_LEFT_SHIFT) : bleKeyboard.release(KEY_LEFT_SHIFT);
        (!button_val[3]) ? bleKeyboard.press(KEY_LEFT_CTRL) : bleKeyboard.release(KEY_LEFT_CTRL);
        (!button_val[4]) ? bleKeyboard.press(KEY_RIGHT_SHIFT) : bleKeyboard.release(KEY_RIGHT_SHIFT);
        (!button_val[5]) ? bleKeyboard.press(KEY_RIGHT_CTRL) : bleKeyboard.release(KEY_RIGHT_CTRL);
        (!button_val[6]) ? bleKeyboard.press(KEY_ESC) : bleKeyboard.release(KEY_ESC);
        (!button_val[7]) ? bleKeyboard.press(KEY_RETURN) : bleKeyboard.release(KEY_RETURN);
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
  bleKeyboard.end();
  ble_connection = 0;
}