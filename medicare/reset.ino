void reset_protocol() {
  if (digitalRead(0) == LOW) {
    oled.clear();
    text("  RESET  ", 11, 2);
    delay(100);
    uint32_t startTime = millis();
    byte i = 0;
    while (digitalRead(0) == LOW) {
      delay(50);
      text(".", i, 4);
      i += 4;
      if (i > 127) i = 127;
    }
    uint32_t endTime = millis();
    if ((endTime - startTime) > 1600) {
      oled.clear();
      text("  RESET  ", 11, 2);
      text("  DONE!  ", 11, 5);
      RMakerWiFiReset(5);
      // RMakerFactoryReset(5);
    }

    else {
      drawer1.write(min_pos);
      drawer2.write(min_pos);
      drawer3.write(min_pos);
      d1 = d2 = d3 = millis();
      f1 = f2 = f3 = 1;
      t1 = millis();
    }
    oled.clear();
  }
}