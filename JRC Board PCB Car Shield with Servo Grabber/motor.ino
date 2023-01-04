void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  } else {
    a = -a;
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }
  if (b > 0) {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  } else {
    b = -b;
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }
  ledcWrite(14, a);
  ledcWrite(15, b);
}

void motor_initiate() {
  ledcSetup(14, 1000, 8);
  ledcSetup(15, 1000, 8);
  ledcAttachPin(lms, 14);
  ledcAttachPin(rms, 15);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  motor(0, 0);
}
