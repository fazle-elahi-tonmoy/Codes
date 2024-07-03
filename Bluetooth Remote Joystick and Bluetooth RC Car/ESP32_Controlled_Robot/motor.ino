void motor(int a, int b) {

  if (a >= 0) {
    analogWrite(lmf, a);
    analogWrite(lmb, 0);
  } else {
    a = -a;
    analogWrite(lmf, 0);
    analogWrite(lmb, a);
  }
  if (b >= 0) {
    analogWrite(rmf, b);
    analogWrite(rmb, 0);
  } else {
    b = -b;
    analogWrite(rmf, 0);
    analogWrite(rmb, b);
  }
}