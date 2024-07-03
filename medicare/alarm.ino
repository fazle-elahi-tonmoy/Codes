void alarm(bool a) {
  if (a) {
    if (millis() - al > 500) {
      al = millis();
      digitalWrite(buzzer, !digitalRead(buzzer));
    }
  } else
    digitalWrite(buzzer, 0);
}