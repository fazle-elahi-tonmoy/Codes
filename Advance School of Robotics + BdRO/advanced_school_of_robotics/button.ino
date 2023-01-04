int button() {
  int c = 0;
p: int t = 0;
  while (!digitalRead(sw)) {
    t++; delay(1); digitalWrite(led, HIGH);
  }
  if (t > 15) {
    digitalWrite(led, LOW);
    c++; t = 0;
    while (digitalRead(sw)) {
      t++; delay(1);
      if (t > 500) return c;
    }
    goto p;
  }
  return c;
}
