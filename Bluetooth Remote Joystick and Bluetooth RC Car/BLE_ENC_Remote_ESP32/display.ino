void home_screen() {
  if (millis() - refresh_timer > 60) {
    refresh_timer = millis();
    display.clearDisplay();
    display.drawBitmap(4, 23, frames[frame], 32, 32, 1);
    text("SMART", 54, 20);
    text("REMOTE", 48, 40);
    display.display();
    frame++;
    frame %= FRAME_COUNT;
  }
}

void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}

void display_icon(int base, int a) {
  display.clearDisplay();
  display.drawRoundRect((a - base) * 32, 0, 32, 32, 8, 1);
  for (int i = 0; i < 4; i++) {
    display.drawBitmap(4 + i * 32, 4, all_icon[i + base], 24, 24, 1);
  }
}

void pot_display() {
  while (!push(l1)) {
    display.clearDisplay();
    for (byte i = 0; i < 4; i++) joystick[i] = analogRead(joystick_pin[i]);
    String value = String(joystick[0]);
    byte charlen = value.length();
    String disp;
    for (int i = 0; i < 4 - charlen; i++) disp += " ";
    disp += value + " " + String(joystick[2]);
    text(disp, 11, 12);
    value = String(joystick[1]);
    charlen = value.length();
    disp = "";
    for (int i = 0; i < 4 - charlen; i++) disp += " ";
    disp += value + " " + String(joystick[3]);
    text(disp, 11, 36);
    display.display();
  }
}

void button_display() {
  while (1) {
    display.clearDisplay();
    for (byte i = 0; i < 6; i++) {
      button_val[i] = digitalRead(button[i]);
      text(String(button_val[i]), i * 21 + 4, 12);
    }
    Lencoder_read();
    Rencoder_read();
    String value = String(Lposition);
    byte charlen = value.length();
    String disp;
    for (int i = 0; i < 4 - charlen; i++) disp += " ";
    disp += value + " " + String(Rposition);
    text(disp, 11, 36);
    display.display();
    if (!button_val[1] && !button_val[0]) break;
  }
}

void console_display() {
  uint32_t timer = millis();
  while (1) {
    int p = recheck();
    if (p) {
      display.clearDisplay();
      String value = String(p, 2);
      byte charlen = value.length();
      String disp;
      for (byte i = 0; i < 10 - charlen; i++) disp += "0";
      disp += value;
      text(disp, 4, 24);
      display.display();
      timer = millis();
    }
    if (millis() - timer > 3000) {
      display.clearDisplay();
      display.display();
    }
  }
}