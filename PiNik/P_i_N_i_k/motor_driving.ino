void mos(short int a , short int b) {
  if (a >= 0) {
    (spe < 0) ? analogWrite(lmf, a + (spe * ((100 * a) / 250)) / 100) : analogWrite(lmf, a) ;
    analogWrite(lmb, 0);
  }
  else if (a < 0) {
    a = -a;
    (spe < 0) ? analogWrite(lmb, a + (spe * ((100 * a) / 250)) / 100) : analogWrite(lmb, a) ;
    analogWrite(lmf, 0);
  }
  if (b >= 0) {
    (spe > 0) ? analogWrite(rmf, b - (spe * ((100 * b) / 250)) / 100) : analogWrite(rmf, b) ;
    analogWrite(rmb, 0);
  }
  else if (b < 0) {
    b = -b;
    (spe > 0) ? analogWrite(rmb, b - (spe * ((100 * b) / 250)) / 100) : analogWrite(rmb, b) ;
    analogWrite(rmf, 0);
  }
  return ;
}

void motorSpeedB(short int a, short int b) {
  mos(-a, -b);
}

void motorSpeedR(short int a, short int b) {
  mos(a, -b);
}

void motorSpeedL(short int a, short int b) {
  mos(-a, b);
}

void braking_mechanism(float a) {
  if (cl != 0)motorSpeedB(250, 250);
  brake = cl / d;
  delay(a * brake);
  k30 = 0;
  k90 = 0;
  mov = 0;
  cross = 0;
  cl = base;
  k = 0;
}

void head_light(byte a) {
  if (a == 1) {
    digitalWrite(head_left1, HIGH);
    digitalWrite(head_right1, HIGH);
    digitalWrite(head_left2, HIGH);
    digitalWrite(head_right2, HIGH);
  }
  else {
    digitalWrite(head_left1, LOW);
    digitalWrite(head_right1, LOW);
    digitalWrite(head_left2, LOW);
    digitalWrite(head_right2, LOW);
  }
}

void motor_direction() {
  byte c = 0;
  while (digitalRead(mb) == HIGH) {
    display.clearDisplay();
    (c == 0) ? text("   LEFT   ", 04, 0) : text("  RIGHT  ", 10, 0);
    text("  MOTOR  ", 10, 25);
    text("  TOGGLE  ", 04, 50);
    display.display();
    if (digitalRead(ub) == LOW) c = 1;
    else if (digitalRead(db) == LOW) c = 0;
  }
  if (long_press(1) == 0) {
    (c == 0) ? lvalue = (lvalue % 10) * 10 + lvalue / 10 : rvalue = (rvalue % 10) * 10 + rvalue / 10;
    lmf = lvalue / 10; lmb = lvalue % 10; rmf = rvalue / 10; rmb = rvalue % 10;
    (c == 0) ? EEPROM.write(36, lvalue) : EEPROM.write(37, rvalue);
    delay(10);
  }
}

void beeping(int a) {
  digitalWrite(buzzer, HIGH); delay(50);
  digitalWrite(buzzer, LOW);
  if (a > 1) {
    delay(50); beeping(a - 1);
  }
}
