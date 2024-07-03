int push(int pin_number) {
  int count = 0;
repeat:
  unsigned long int timer = 0;
  if (digitalRead(pin_number) == 0) {       //if the button is pressed
    delay(50);                              //debounce delay
    while (digitalRead(pin_number) == 0) {  //check if the button is still pressed
      delay(20);
      timer += 20;
      digitalWrite(led, 1);
    }
    digitalWrite(led, 0);
    if (timer != 0) {  //if the button was really pressed
      timer = 0;
      count++;
      while (digitalRead(pin_number) == 1) {
        delay(10);
        timer += 10;
        if (timer > 1000) return count;
      }
      goto repeat;
    }
  } else return 0;
}