byte push(byte button) {
  int t = 0;
  bool flag = 1;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    while (!digitalRead(button)) {
      delay(10);
      t += 10;
    }
    if (t) return 1;
  }
  return 0;
}
