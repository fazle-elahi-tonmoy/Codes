void press() {
  uint32_t t = 0;
  if (!digitalRead(0)) {  //if button is pressed
    delay(50);
    while (!digitalRead(0)) {  //wait untill the button is released
      delay(50);
      t++;
    }
    if (t > 0) {
      mode = !mode;
      digitalWrite(32, mode);
    }
  }
}