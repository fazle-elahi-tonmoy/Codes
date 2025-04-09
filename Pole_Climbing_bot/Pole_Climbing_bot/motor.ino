void motor(int a, int b) {
  digitalWrite(IN1, a > 0);
  digitalWrite(IN2, a < 0);
  digitalWrite(IN3, b > 0);
  digitalWrite(IN4, b < 0);
}