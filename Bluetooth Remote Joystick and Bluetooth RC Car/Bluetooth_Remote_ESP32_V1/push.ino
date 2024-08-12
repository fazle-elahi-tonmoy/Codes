byte press(byte pin) {
  byte count = 0;
p:  uint32_t t = 0;
  if (digitalRead(pin) == 0) {       //if button is pressed
    delay(50);                       //debounce
    digitalWrite(led, 1);
    while (digitalRead(pin) == 0) {  //wait untill the button is released
      delay(50);
      t++;
    }
    digitalWrite(led, 0);
    if (t > 0) {
      count++;
      t = 0;
      while (digitalRead(pin) == 1) {  //wait untill button is pressed again
        delay(50);
        t+=50;
        if(t>=1000) return count; //if it waits more than 1sec
      }
      goto p;
    }
  }
  else {
    return count;
  }
}
