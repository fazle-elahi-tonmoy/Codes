bool long_press(byte pin, byte time) {
  uint16_t t = 0;
  if (!digitalRead(pin)) {
    delay(20);
    while (!digitalRead(pin)) {
      delay(20);
      t++;
      if (t > time) return 1;
    }
  }
  return 0;
}