void alarm() {
  if (timer3 - millis() > 50) {
    timer3 = millis();
    tone(buzzer_pin, alarm_freq,0);
    alarm_freq++;
    if (alarm_freq > 3000) alarm_freq = 2000;
  }
}