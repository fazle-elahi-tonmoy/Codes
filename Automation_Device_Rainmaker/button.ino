int press(int button) {
  bool lp = 0, sp = 0;
  if (digitalRead(button) == LOW) {
    delay(15);
    uint32_t startTime = millis();
    while (digitalRead(button) == LOW) {
      delay(15);
      if (((millis() - startTime) > long_press_timer) && !lp) {
        oled.clear();
        text("LONG PRESS", 4, 4);
        lp = 1;
      }

      else if (((millis() - startTime) >= 30) && !sp) sp = 1;
    }
    if (lp) return 2;
    else if (sp) return 1;
    else return 0;
  }

  else return 0;
}