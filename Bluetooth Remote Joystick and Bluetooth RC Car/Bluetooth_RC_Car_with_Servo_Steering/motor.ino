void motor(int a) {
  digitalWrite(mf, (a > 0));
  digitalWrite(mb, (a < 0));
}