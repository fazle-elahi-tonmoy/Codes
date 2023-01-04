void button() {
  l1 = digitalRead(6);
  l2 = digitalRead(8);
  r1 = digitalRead(10);
  r2 = digitalRead(9);
  lmb = digitalRead(11);
  rmb = digitalRead(12);
  pl = map(analogRead(A6), 100, 1000, 0, 9);
  pr = map(analogRead(A7), 100, 1000, 0, 9);
  lx = analogRead(0);
  ly = analogRead(1);
  rx = analogRead(2);
  ry = analogRead(3);
}
