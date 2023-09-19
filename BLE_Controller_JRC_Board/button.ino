byte push(byte button) {
  int t = 0;
  bool flag = 1;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    while (!digitalRead(button)) {
      delay(10);
      t += 10;

      if (t > 2000) digitalWrite(indicator, 0);
      else if (t > 500) digitalWrite(indicator, 1);
    }
    digitalWrite(indicator, 0);
    if (t > 1000) return 3;
    else if (t > 500) return 2;
    else if (t > 0) return 1;
  }
  return 0;
}

byte side_press(byte a) {
  short int p = 0;
  while (digitalRead(up) == LOW || digitalRead(down) == LOW) {
    p++;
    delay(1);
    if (digitalRead(up) == LOW && digitalRead(down) == LOW) break;
    if (p >= 500 || a == 1) return 1;
  }
  return 0;
}
