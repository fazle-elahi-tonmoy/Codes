byte hour = 0, minute = 0, second = 0, decimal = 0;
uint32_t m = millis();

void stop_watch() {
  while (1) {
    oled.setTextSize(2);
    drawStop();
    while (digitalRead(SW))
      ;
    while (!digitalRead(SW))
      ;

resume:
    while (digitalRead(SW)) {
      time_count();
      drawStop();
    }
    while (!digitalRead(SW))
      ;

    while (1) {
      if (push(up)) {
        hour = 0;
        minute = 0;
        second = 0;
        decimal = 0;
        break;
      }
      if (push(SW)) goto resume;
    }
  }
}

void drawStop() {
  oled.clearDisplay();
  text("STOPWATCH", 11, 12);
  oled.setCursor(04, 36);
  oled.print(String(hour) + ":");
  (minute < 10) ? oled.print("0" + String(minute) + ":") : oled.print(String(minute) + ":");
  (second < 10) ? oled.print("0" + String(second) + ".") : oled.print(String(second) + ".");
  (decimal < 10) ? oled.print("0" + String(decimal)) : oled.print(decimal);
  oled.display();
}

void time_count() {
  if (millis() - m >= 1000) {
    m = millis();
    second++;
    if (second > 59) {
      second = 0;
      minute++;
    }
    if (minute > 59) {
      minute = 0;
      hour++;
    }
  }
  decimal = (millis() - m) / 10;
}