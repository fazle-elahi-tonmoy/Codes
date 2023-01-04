void reset_protocol() {
  if (digitalRead(reset_button) == LOW) {
    oled.clear();
    text("  RESET  ", 11, 2);
    delay(100);
    uint32_t startTime = millis();
    byte i = 0;
    while (digitalRead(reset_button) == LOW) {
      delay(50);
      text(".", i, 4);
      i += 4;
      if (i > 127) i = 127;
    }
    uint32_t endTime = millis();
    if ((endTime - startTime) > 1600) {
      homepage = false;
      oled.clear();
      text("  RESET  ", 11, 2);
      text("  DONE!  ", 11, 5);
      // RMakerWiFiReset(2);
      RMakerFactoryReset(2);
    }

    oled.clear();
  }
}