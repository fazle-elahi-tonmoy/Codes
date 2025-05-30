int push() {
  int count = 0;
again:
  int timer = 0;
  if (!digitalRead(button)) {
    delay(20);
    bool flag = 0;
    while (!digitalRead(button)) {
      delay(10);
      timer += 10;
      if (timer > 1000) flag = 1;
    }
    if (flag) return -1;
    if (timer) {
      count++;
      timer = 0;
      while (digitalRead(button)) {
        delay(10);
        timer += 10;
        if (timer > 1000) return count;
      }
      goto again;
    }
  }
  return count;
}