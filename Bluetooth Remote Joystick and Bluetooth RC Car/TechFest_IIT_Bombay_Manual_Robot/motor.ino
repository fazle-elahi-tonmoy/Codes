void motor(int a, int b) {
  if (a == 3) {
    digitalWrite(lmf1, 1);
    digitalWrite(lmf2, 0);
    digitalWrite(lmb1, 1);
    digitalWrite(lmb2, 0);
  }

  else if (a == 2) {
    digitalWrite(lmf1, 1);
    digitalWrite(lmf2, 0);
    digitalWrite(lmb1, 0);
    digitalWrite(lmb2, 0);
  }

  else if (a == 1) {
    digitalWrite(lmf1, 0);
    digitalWrite(lmf2, 0);
    digitalWrite(lmb1, 1);
    digitalWrite(lmb2, 0);
  }

  else if (a == -3) {
    digitalWrite(lmf1, 0);
    digitalWrite(lmf2, 1);
    digitalWrite(lmb1, 0);
    digitalWrite(lmb2, 1);
  }

  else if (a == -2) {
    digitalWrite(lmf1, 0);
    digitalWrite(lmf2, 1);
    digitalWrite(lmb1, 0);
    digitalWrite(lmb2, 0);
  }

  else if (a == -1) {
    digitalWrite(lmf1, 0);
    digitalWrite(lmf2, 0);
    digitalWrite(lmb1, 0);
    digitalWrite(lmb2, 1);
  }

  else {
    digitalWrite(lmf1, 0);
    digitalWrite(lmf2, 0);
    digitalWrite(lmb1, 0);
    digitalWrite(lmb2, 0);
  }

  if (b == 3) {
    digitalWrite(rmf1, 1);
    digitalWrite(rmf2, 0);
    digitalWrite(rmb1, 1);
    digitalWrite(rmb2, 0);
  }

  else if (b == 2) {
    digitalWrite(rmf1, 1);
    digitalWrite(rmf2, 0);
    digitalWrite(rmb1, 0);
    digitalWrite(rmb2, 0);
  }

  else if (b == 1) {
    digitalWrite(rmf1, 0);
    digitalWrite(rmf2, 0);
    digitalWrite(rmb1, 1);
    digitalWrite(rmb2, 0);
  }

  else if (b == -3) {
    digitalWrite(rmf1, 0);
    digitalWrite(rmf2, 1);
    digitalWrite(rmb1, 0);
    digitalWrite(rmb2, 1);
  }

  else if (b == -2) {
    digitalWrite(rmf1, 0);
    digitalWrite(rmf2, 1);
    digitalWrite(rmb1, 0);
    digitalWrite(rmb2, 0);
  }

  else if (b == -1) {
    digitalWrite(rmf1, 0);
    digitalWrite(rmf2, 0);
    digitalWrite(rmb1, 0);
    digitalWrite(rmb2, 1);
  }

  else {
    digitalWrite(rmf1, 0);
    digitalWrite(rmf2, 0);
    digitalWrite(rmb1, 0);
    digitalWrite(rmb2, 0);
  }

}
