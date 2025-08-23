void motor(int a, int b) {
  digitalWrite(lmf, (a > 0));
  digitalWrite(lmb, (a < 0));
  digitalWrite(rmf, (b > 0));
  digitalWrite(rmb, (b < 0));
}