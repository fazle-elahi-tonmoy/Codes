void sensor() {
  (analogRead(32) < 3000) ? s1 = 0 : s1 = 1;
  (analogRead(33) < 3000) ? s2 = 0 : s2 = 1;
  (analogRead(35) < 3000) ? s3 = 0 : s3 = 1;
}

void sensor_test() {
  oled.clear();
  refresh = 1;
  while (digitalRead(0)) {
    text("   " + String(analogRead(32)) + "   ", 04, 0);
    text("   " + String(analogRead(33)) + "   ", 04, 3);
    text("   " + String(analogRead(35)) + "   ", 04, 6);
  }
  push();
}