void left_servo_test() {
  while (1) {
    for (int i = 10; i <= 150; i++) {
      left_hand.write(i); delay(5);
    }
    for (int i = 150; i >= 10; i--) {
      left_hand.write(i); delay(5);
    }
  }
}

void right_servo_test() {
  while (1) {
    for (int i = 10; i <= 150; i++) {
      right_hand.write(i); delay(5);
    }
    for (int i = 150; i >= 10; i--) {
      right_hand.write(i); delay(5);
    }
  }
}
