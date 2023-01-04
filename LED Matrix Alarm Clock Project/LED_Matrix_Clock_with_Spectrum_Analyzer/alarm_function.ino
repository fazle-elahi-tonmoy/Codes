void alarm_function() {
  if (millis() - al > beeping_interval) {
    al = millis();
    digitalWrite(buzzer, !digitalRead(buzzer));
    if (alarm2) digitalWrite(lamp, !digitalRead(lamp));
  }
  if (millis() - m2 > mute_timer) {
    alarm = 0; alarm2 = 0; digitalWrite(buzzer, 0); snooze = 0;
    if (snooze_count > 0) {
      snooze = 1; snooze_count--;
      sz = millis();
    }
  }
}
