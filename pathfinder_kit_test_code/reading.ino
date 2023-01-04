
void analog_display() {
  while (1) {
    byte i;
    for (i = 0; i < 6; i++) (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    for (i = 0; i < 3; i++) {
      value = String(s[i]);
      (s[i] < 100) ? text(value + "  ", 70, 5 - i * 2) : text(value + " ", 70, 5 - i * 2);
    }
    for (i = 3; i < 6; i++) {
      value = String(s[i], 10);
      (s[i] < 100) ? text(value + "  ", 10, (i - 3) * 2 + 1) : text(value + " ", 10, (i - 3) * 2 + 1);
    }
  }
}