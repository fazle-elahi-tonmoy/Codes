bool push(byte pin) {
  uint32_t timer = 0;
  if (digitalRead(pin) == 1) {
    delay(20);  //debounce delay
    while (digitalRead(pin) == 1) {
      delay(20);
      timer += 20;
    }
    if (timer) return 1;
  }
  return 0;
}