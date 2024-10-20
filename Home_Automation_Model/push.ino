bool push(byte pin_number) {
  uint32_t timer = 0;
  if (!digitalRead(pin_number)) {       //if the button is pressed
    delay(20);                          //debounce delay
    while (!digitalRead(pin_number)) {  //wait untill the button is released
      delay(20);
      timer++;
    }
    if (timer) return 1;  //check is if the button is really pressed
    else return 0;
  }

  return 0;
}