byte press(byte a) {
  byte count = 0;
location:
  uint32_t t = 0;
  if (!digitalRead(a)) {
    delay(20);  //debounce
    digitalWrite(LED, 1);
    while (!digitalRead(a)) {
      delay(1);
      t++;
      if (t > 500) digitalWrite(LED, 0);
      if (theif) alarm();
    }
    digitalWrite(LED, 0);
    if (t > 500) return count + 100;
    else if (t > 0) {
      count++;
      t = 0;
      while (digitalRead(a))
        if (theif) alarm();
      goto location;
    }
  }
  return count;
}
