void motor(int a, int b) {
  if (a >= 0) {
    analogWrite(left_motor_forward, a);
    analogWrite(left_motor_backward, 0);
  }
  else {
    a = -a;
    analogWrite(left_motor_forward, 0);
    analogWrite(left_motor_backward, a);
  }
  if (b >= 0) {
    analogWrite(right_motor_forward, b);
    analogWrite(right_motor_backward, 0);
  }
  else {
    b = -b;
    analogWrite(right_motor_forward, 0);
    analogWrite(right_motor_backward, b);
  }
}

void headlight(bool a){
  (a==0)? digitalWrite(head_light1, LOW) :digitalWrite(head_light1, HIGH);
  (a==0)? digitalWrite(head_light2, LOW) :digitalWrite(head_light2, HIGH);
}
