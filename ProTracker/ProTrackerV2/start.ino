void starting_sequence() {
  while (!power_state) {
    if (!digitalWrite(POW_PIN)) {
      delay(20);
      uint16_t t = 0;
      while (!digitalWrite(POW_PIN)) {
        delay(20);
        t++;
        if (t > 100) {
          if (power_state) ESP.restart();
          else {
            power_state = 1;
            digitalWrite(buzzer, 1);
            delay(100);
            digitalWrite(buzzer, 0);
            delay(100);
            digitalWrite(buzzer, 1);
            delay(100);
            digitalWrite(buzzer, 0);
          }
        }
      }
    }
  }
}