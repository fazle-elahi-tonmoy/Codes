void reminder_sys() {
  if (millis() - reminder > 60000) {
    reminder = millis();
    for (int i = 0; i < 4; i++) {
      digitalWrite(buzzer, 1);
      delay(50);
      digitalWrite(buzzer, 0);
      delay(50);
    }
  }
}