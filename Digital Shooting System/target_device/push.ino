byte push() {
  byte cl = 0;
repeat:
  uint32_t t = 0;
  if (digitalRead(button)) {
    delay(20);
    while (digitalRead(button)) {
      delay(20);
      t++;
    }
    if (t) {
      cl++;
      t = 0;
      while (!digitalRead(button)) {
        delay(1);
        t++;
        if (t > 1000) return cl;
      }
      goto repeat;
    }
  }
  return 0;
}