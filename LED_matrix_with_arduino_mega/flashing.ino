void flashing(char ch[], int a) {
  int x = strlen(ch);
  int s = 0;
  while (s < x) {
    m2 = millis();
    if (m2 - m1 > a) {
      m1 = m2;
      for (int i = s ; i < s + 4; i++) {
        if (ch[s] == ' ') s++;
        else displayletter(ch[i],(i - s) * 5);
      }
      s += 4;
    }
    showing();
  }

  m1 = m2;
  while (m2 - m1 < a * 2) {
    m2 = millis();
    showing();
  }
}
