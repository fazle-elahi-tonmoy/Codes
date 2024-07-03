void incoming() {
  if (Serial1.available()) {
    while (Serial1.available()) {
      char x = Serial1.read();
      Serial.print(x);
      if (x == ',') bleKeyboard.write(KEY_RIGHT_ARROW);
      else if (x == ';') {
        bleKeyboard.write(KEY_RETURN);
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_LEFT_ARROW);
        delay(10);
        bleKeyboard.releaseAll();
      }

      else bleKeyboard.write(x);
    }
    inc = 1;
    scan = 0;
  }
}