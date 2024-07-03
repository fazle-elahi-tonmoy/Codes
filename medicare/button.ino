void push_control() {
  byte x = push();
  if (x == 2) {
    oled.clear();
    refresh = 1;
    byte count = 1, temp = 0;
    uint32_t startTime = millis();
    while (1) {
      if (temp != count) {
        startTime = millis();
        temp = count;
        if (temp == 1) {
          text("   OPEN   ", 04, 02);
          text(" DRAWER 1 ", 04, 05);
        } else if (temp == 2) {
          text("   OPEN   ", 04, 02);
          text(" DRAWER 2 ", 04, 05);
        } else if (temp == 3) {
          text("   OPEN   ", 04, 02);
          text(" DRAWER 3 ", 04, 05);
        } else if (temp == 4) {
          text("   OPEN   ", 04, 02);
          text("ALL DRAWER", 04, 05);
        } else if (temp == 5) {
          text("  CHECK  ", 11, 02);
          text("  VITALS  ", 04, 05);
        } else if (temp == 6) {
          text("  CHECK  ", 11, 02);
          text("  SENSOR  ", 04, 05);
        } else if (temp == 7) {
          text("   WiFi   ", 04, 02);
          text("  RESET  ", 11, 05);
        } else if (temp == 8) {
          text(" FACTORY ", 11, 02);
          text("  RESET  ", 11, 05);
        }
      }
      if (millis() - startTime > 5000) return;
      byte r = push();
      if (r == 1) {
        count++;
        if (count > 8) count = 1;
      }

      else if (r == 2) {
        if (count == 1) {
          drawer1.write(min_pos);
          d1 = millis();
          f1 = 1;
          t1 = millis();
        } else if (count == 2) {
          drawer2.write(min_pos);
          d2 = millis();
          f2 = 1;
          t1 = millis();
        } else if (count == 3) {
          drawer3.write(min_pos);
          d3 = millis();
          f3 = 1;
          t1 = millis();
        } else if (count == 4) {
          drawer1.write(min_pos);
          drawer2.write(min_pos);
          drawer3.write(min_pos);
          d1 = d2 = d3 = millis();
          f1 = f2 = f3 = 1;
          t1 = millis();
        } else if (count == 5) full_checkup();
        else if (count == 6) sensor_test();
        else if (count == 7) RMakerWiFiReset(5);
        else if (count == 8) RMakerFactoryReset(5);
        return;
      }
    }
    oled.clear();
  }
}

byte push() {
  uint32_t timer = 0;
  bool long_press = 0;
  if (!digitalRead(0)) {
    delay(20);
    while (!digitalRead(0)) {
      delay(20);
      timer += 20;
      if (timer > 500 && !long_press) {
        long_press = 1;
        oled.clear();
        text(" SELECTED ", 04, 03);
      }
    }
    if (long_press) return 2;
    else if (timer > 0) return 1;
  }
  return 0;
}