void motor(int a, int b) {
  if (a >= 0) {
    digitalWrite(left_motor_forward, 1);
    digitalWrite(left_motor_backward, 0);
  }
  else {
    a = -a;
    digitalWrite(left_motor_forward, 0);
    digitalWrite(left_motor_backward, 1);
  }
  if (b >= 0) {
    digitalWrite(right_motor_forward, 1);
    digitalWrite(right_motor_backward, 0);
  }
  else {
    b = -b;
    digitalWrite(right_motor_forward, 0);
    digitalWrite(right_motor_backward, 1);
  }
  analogWrite(left_motor_speed, a);
  analogWrite(right_motor_speed, b);
}

void braking() {
  if (brake > 0) motor(-250, -250); delay(brake);
  motor(0, 0); delay(50);
}
