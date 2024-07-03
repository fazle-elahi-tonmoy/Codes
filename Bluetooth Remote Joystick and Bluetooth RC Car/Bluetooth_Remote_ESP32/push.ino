byte press(byte pin) {
  byte count = 0;
p:  uint32_t t = 0;
  if (digitalRead(pin) == 0) {       //if button is pressed
    delay(50);                       //debounce
    while (digitalRead(pin) == 0) {  //wait untill the button is released
      delay(50);
      t++;
    }
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


byte push(byte button) {
  int t = 0;
  bool flag = 1;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    while (!digitalRead(button)) {
      delay(10);
      t += 10;
    }
    if (t) return 1;
  }
  return 0;
}
