void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    oled.clear();
    text("CLOCK FAIL", 4, 3);
    refresh = 1;
    return;
  }
  oled.setCursor(4, 0);
  oled.print(" ");
  oled.print(&timeinfo, "%I:%M:%S");
  oled.println(" ");
  // char timeHour[3];
  // strftime(timeHour,3, "%H", &timeinfo);
}

void home_screen() {

  if (homepage && (millis() - t1 > 1000)) {
    if (refresh) {
      oled.clear();
      refresh = 0;
    }
    if (WiFi.status() != WL_CONNECTED) {
      text(" NO WiFi ", 11, 3);
      refresh = 1;
    } else {
      t1 = millis();
      printLocalTime();
      text(" BPM: " + String(beatAvg) + "  ", 11, 03);
      text(" O2: " + String(SpO2) + "%  ", 11, 06);
    }
  }
}