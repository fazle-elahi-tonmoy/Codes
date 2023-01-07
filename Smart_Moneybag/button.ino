int press(byte a) {
  byte count = 0;
location:
  uint32_t t = 0;
  if (!digitalRead(a)) {
    delay(20);  //debounce
    while (!digitalRead(a)) {
      delay(10);
      t += 10;
      if (t > 500) return -1;
    }
    if (t > 0) {
      count++;
      t = 0;
      while (digitalRead(a)) {
        delay(1);
        t++;
        if (t > 500) return count;
      }
      goto location;
    }
  }
  return count;
}
