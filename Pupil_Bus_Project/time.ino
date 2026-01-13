void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    text("CLOCK FAIL", 4, 50, 2);
    return;
  }
  display.setTextSize(2);
  display.setCursor(4, 50);
  display.print(" ");
  display.print(&timeinfo, "%I:%M:%S");
  display.print(" ");
}
