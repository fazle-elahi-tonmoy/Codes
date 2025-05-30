void motor(int a, int b) {
  digitalWrite(lmf, (a > 0));
  digitalWrite(lmb, (a < 0));
  digitalWrite(rmf, (b > 0));
  digitalWrite(rmb, (b < 0));
  analogWrite(lms, min(255, abs(a)));
  analogWrite(rms, min(255, abs(b)));
  Serial.println(String(min(255, abs(a))) + " " + String(min(255, abs(b))));
}