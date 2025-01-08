void timer_set() {
  int temp = -1;
  int value = charge_time;
  while (1) {
    if (charge_time != temp) {
      temp = charge_time;
      display.clearDisplay();
      text("ChargeTime", 04, 12);
      text(String(charge_time * 10) + "s", 04, 40);
      display.display();
    }
    byte r = push(sw1);
    if (r == 1 && charge_time > 0) charge_time --;
    else if (r == 2) {
      display.clearDisplay();
      text("CANCELLED!", 04, 24);
      display.display();
      charge_time = value;
      delay(1000);
      return;
    }

    r = push(sw2);
    if (r == 1 && charge_time < 250) charge_time ++;
    else if (r == 2) {
      EEPROM.write(0, charge_time);
      EEPROM.commit();
      display.clearDisplay();
      text(" UPDATED! ", 04, 24);
      display.display();
      delay(1000);
      return;
    }
  }
}