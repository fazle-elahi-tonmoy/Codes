void button() {
  if (digitalRead(sw) == 0) { // if pressed, it will go to low state
    digitalWrite(front_light, 1); //indicate that you have pressed the button
    while (digitalRead(sw) == 0) delay(15); //if you kept pressing the button, it will not do anything further untill you release it
    digitalWrite(front_light, 0); //indicate that you have released the button
    mode = !mode; //changing the sensor detecting mode
  }
}
