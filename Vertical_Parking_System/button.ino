byte push(byte a) {
  uint32_t timer = 0;
  bool flag = 1;
  if (!digitalRead(a)) {
    // Serial.println("Pressed");
    delay(50);  //debounce delay
    while (!digitalRead(a)) {
      delay(10);
      timer += 10;
      if (timer > long_press_timer && flag) {
        flag = 0;
        text("    Long Pressed    ", 0, 2);
      }
    }
    if (!flag) return 2;
    else if (timer) return 1;
  }
  return 0;
}