void press_function() {
  button_read = press(button);
  if (button_read) {
    if (button_read == 101 && !lock) {
      blink(3);
      waiting_for_pass_input();
      password_reading();
      password = pass_read;
      EEPROM.write(0, password);
    }

    else if (button_read > 100) {  //password verifying  mechanism
      password_reading();
      if (pass_read == password) {
        lock = 0;
        theif = 0;
        trigger = 0;
        EEPROM.write(1, lock);
      }
    }

    else if (button_read == 100 and !theif) {  //locking the moneybag
      blink(1);
      delay(10000);
      lock = 1;
      EEPROM.write(1, lock);
      blink(1);
    }
  }
}

void password_reading() {
  if (button_read >= 100) button_read -= 100;
  pass_read = button_read * 10;
  waiting_for_pass_input();
  pass_read += button_read;
}

void waiting_for_pass_input() {
  button_read = 0;
  while (!button_read) {
    button_read = press(button);
    if (theif) alarm();
  }
  button_read -= 100;
}