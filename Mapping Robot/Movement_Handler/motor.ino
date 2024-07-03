void motor(int a, int b) {
  if (a >= 0) {
    digitalWrite(motor_pin[0], 1);
    digitalWrite(motor_pin[1], 0);
  } else {
    a = -a;
    digitalWrite(motor_pin[0], 0);
    digitalWrite(motor_pin[1], 1);
  }
  if (b >= 0) {
    digitalWrite(motor_pin[2], 1);
    digitalWrite(motor_pin[3], 0);
  }

  else {
    b = -b;
    digitalWrite(motor_pin[2], 0);
    digitalWrite(motor_pin[3], 1);
  }

  if (a > 255) a = 255;
  if (b > 255) b = 255;
  ledcWrite(10, a);
  ledcWrite(11, b);
}