void led_blinking() {
  if (millis() - timer > 1000) {
    timer = millis();  //timer reset
    timer2 = millis();
    reading = 1;
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
  }

  if (millis() - timer2 > 500 && reading) {
    reading = 0;
    int x = analogRead(IR_receiver);
    (x < mid_value) ? x = 0 : x = 1;
    if (led_state != x && lock && !theif) {
      theif = 1;
      timer4 = millis();
    }
    Serial.println(String(led_state) + " " + String(x) + " " + String(theif));
  }
}