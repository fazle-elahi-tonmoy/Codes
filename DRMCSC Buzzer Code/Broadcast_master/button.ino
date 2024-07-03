int push(int pin_number) {
  unsigned long int timer = 0;
  if (digitalRead(pin_number) == 0) {       //if the button is pressed
    delay(50);                              //debounce delay
    while (digitalRead(pin_number) == 0) {  //check if the button is still pressed
      delay(20);
      timer += 20;
      if (timer > 1000) digitalWrite(led, 1);
    }
    digitalWrite(led, 0);
    if (timer == 0) return 0;
    else if (timer <= 1000) return 1;
    else return 2;
  } else return 0;
}