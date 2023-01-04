void changing(char ch[255], int a) {
  int x = strlen(ch);
  int s = 0;
  (x % 4 == 0) ? s = x / 4 : s = x / 4 + 1;
  int state = 0;
  while (state < s) {
    m2 = millis();
    if (m2 - m1 > a) {
      m1 = m2;
      checking(ch, state, x-state);
      state++;
    }
    showing();
  }

  m1 = m2;
  while (m2 - m1 < a * 2) {
    m2 = millis();
    showing();
  }
}
