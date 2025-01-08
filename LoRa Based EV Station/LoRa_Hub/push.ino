byte push(byte pin) {
  uint32_t timer = 0;
  bool flag = 0;
  if (!digitalRead(pin)) {
    delay(50);
    while (!digitalRead(pin)) {
      delay(20);
      timer++;
      if (timer > 50 && !flag) {
        flag = 1;
        display.clearDisplay();
        text("Long Press", 04, 24);
        display.display();
      }
    }
    if (flag) return 2;
    else if (timer) return 1;
  }
  return 0;
}