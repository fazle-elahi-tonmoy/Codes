void IR_Testing() {
  if (millis() - timer > 100) {
    timer = millis();  //timer reset
    timer2 = millis();
    reading = 1;
    led_state = !led_state;
    digitalWrite(IR_Tx, led_state);
  }

  if (millis() - timer2 > 50 && reading) {
    reading = 0;
    int x = analogRead(IR_receiver);
    (x < mid_value) ? x = 1 : x = 0;
    if (led_state != x && lock && !theif && !trigger) {
      trigger = 1;
      timer4 = millis();
    }
    if(debug) Serial.println(String(led_state) + " " + String(x) + " " + String(theif));
  }
}