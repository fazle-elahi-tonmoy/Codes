int sonar() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH, 5000);

  (duration > 0) ? distance = duration* 0.034 / 2 : distance = 0;
  ;
  if (distance == 0) distance = 45;
  return distance;
}