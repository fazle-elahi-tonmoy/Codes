void mos(int a , int b) {
  if (a >= 0) {
    (spe > 0) ? analogWrite(rmf, a - (spe * ((100 * a) / 250)) / 200) : analogWrite(rmf, a);
    analogWrite(rmb, 0);
  }
  else if (a < 0) {
    a = -a;
    analogWrite(rmf, 0);
    (spe > 0) ? analogWrite(rmb, a - (spe * ((100 * a) / 250)) / 200) : analogWrite(rmb, a);
  }
  if (b >= 0) {
    (spe < 0) ? analogWrite(lmf, b + (spe * ((100 * b) / 250)) / 200) : analogWrite(lmf, b);
    analogWrite(lmb, 0);
  }
  else if (b < 0) {
    b = -b;
    analogWrite(lmf, 0);
    (spe < 0) ? analogWrite(lmb, b + (spe * ((100 * b) / 250)) / 200) : analogWrite(lmb, b);
  }
  return ;
}


void motorSpeedL(int speedA, int speedB) {
  mos(speedA, -speedB);
}

void motorSpeedR(int speedA, int speedB) {
  mos(-speedA, speedB);
}
void motorSpeedB(int speedA, int speedB) {
  mos(-speedA, -speedB);
}

void motorSpeedS() {
  mos(0, 0);
}

void braking_mechanism() {
  if (cl != 0) motorSpeedB(10 * sp, 10 * sp);
  brake = cl / d;
  delay(brake);
  k30 = 0;
  k90 = 0;
  mov = 0;
  cross = 0;
  cl = base;
  brake = cl / d;
  k = 0;
}
