byte touch() {
pos:
  uint32_t timer = 0;
  if (digitalRead(TOUCH)) {
    while (digitalRead(TOUCH)) {
      delay(1);
      timer++;
      if (timer > 1000) {
        digitalWrite(PIN_Buzzer, HIGH);
        delay(1000);
        digitalWrite(PIN_Buzzer, LOW);
        return 2;
      }
    }
    timer = 0;
    while (!digitalRead(TOUCH)) {
      delay(1);
      timer++;
      if (timer > 1000) return 1;
    }
    goto pos;
  }
  return 0;
}