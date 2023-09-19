void presentation() {
  if (!ble_connection) bleKeyboard.begin();
  byte mode = 0, temp = 100;
  bool home = 0;
  oled.clearDisplay();
  oled.setTextSize(2);
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 1);
      oled.display();
    }
    if (temp != mode) {
      temp = mode;
      if (mode == 0) {
        oled.clearDisplay();
        text(" VERTICAL ", 4, 12);
        text("   MODE   ", 4, 36);
        if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
        oled.display();
      }

      else if (mode == 1) {
        oled.clearDisplay();
        text("HORIZONTAL", 4, 12);
        text("   MODE   ", 4, 36);
        if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
        oled.display();
      }

      else if (mode == 2) {
        oled.clearDisplay();
        text("   PAGE   ", 4, 12);
        text("   MODE   ", 4, 36);
        if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
        oled.display();
      }
    }


    byte r = push(SW);

    if (ble_connection) {
      if (!digitalRead(down)) {
        if (mode == 0) bleKeyboard.write(KEY_UP_ARROW);
        else if (mode == 1) bleKeyboard.write(KEY_LEFT_ARROW);
        else if (mode == 2) bleKeyboard.write(KEY_PAGE_UP);
        delay(100);
        while (!digitalRead(down)) delay(100);
      }
      if (!digitalRead(up)) {
        if (mode == 0) bleKeyboard.write(KEY_DOWN_ARROW);
        else if (mode == 1) bleKeyboard.write(KEY_RIGHT_ARROW);
        else if (mode == 2) bleKeyboard.write(KEY_PAGE_DOWN);
        delay(100);
        while (!digitalRead(up)) delay(100);
      }
      if (r == 1) {
        home = !home;
        (home) ? bleKeyboard.write(KEY_HOME) : bleKeyboard.write(KEY_END);
      }
    }

    if (r == 2) {
      mode++;
      if (mode > 2) mode = 0;
    }
    if (r == 3) return;
  }
}

void media() {
  if (!ble_connection) bleKeyboard.begin();
  oled.clearDisplay();
  oled.setTextSize(2);
  text("   MEDIA   ", 4, 12);
  text("   MODE   ", 4, 36);
  if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
  oled.display();
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 1);
      oled.display();
    }
    byte r = push(SW);
    if (ble_connection) {
      if (!digitalRead(up)) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        delay(50);
      }

      if (!digitalRead(down)) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
        delay(50);
      }
      if (r == 1) bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      else if (r == 2) bleKeyboard.write(KEY_MEDIA_MUTE);
    }
    if (r == 3) return;
  }
}