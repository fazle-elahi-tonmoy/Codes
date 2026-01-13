byte push(byte a) {
  uint32_t timer = 0;
  if (!digitalRead(a)) {
    delay(50);
    while (!digitalRead(a)) {
      delay(10);
      timer += 10;
      if (timer > 2000) digitalWrite(led, 1);
    }
    digitalWrite(led, 0);
    if (timer > 2000) return 1;
    else if (timer > 0) return 2;
  }
  return 0;
}

void push_function() {
  byte r = push(button);
  if (r) {
    if (r == 1) {
      vehicle_state = !vehicle_state;
      (vehicle_state) ? vehicle_id = vehicle2_id : vehicle_id = vehicle1_id;
    }

    else if (r == 2) {
      debugging_mode = !debugging_mode;
      display.clearDisplay();
      text("DEBUGGING", 11, 8, 2);
      (debugging_mode) ? text("  ACTIVE  ", 04, 40, 2) : text("   OFF   ", 11, 40, 2);
      display.display();
      delay(1000);
      if (debugging_mode) SerialBT.begin("GPS Test");
      else SerialBT.end();
    }
  }
}
