void text(String t, int x, int y, int s) {
  display.setTextSize(s);
  display.setCursor(x, y);
  display.print(t);
}

void starting_screen() {
  display.clearDisplay();
  signal_strength();
  (vehicle_state) ? text("DHAKA METRO X 22-2222", 0, 11, 1) : text("DHAKA METRO X 11-1111", 0, 11, 1);
  (gps_connected) ? text("GPS: " + String(gps.satellites.value()) + " Connected", 15, 20, 1) : text("Searching for GPS", 12, 20, 1);
  (vehicle_state) ? text(" BUS-002 ", 11, 32, 2) : text(" BUS-001 ", 11, 32, 2);
  printLocalTime();
  display.display();
}

void signal_strength() {
  int x = WiFi.RSSI();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(WiFi.localIP());
  display.drawBitmap(103, 0, network, 8, 8, SSD1306_WHITE);
  if (x == 0 || x > 100) display.drawBitmap(113, 0, no_signal, 8, 8, SSD1306_WHITE);
  else {
    if (x < 60) display.drawBitmap(113, 0, bad, 8, 8, SSD1306_WHITE);
    if (x < 50) display.drawBitmap(117, 0, medium, 8, 8, SSD1306_WHITE);
    if (x < 40) display.drawBitmap(121, 0, good, 8, 8, SSD1306_WHITE);
    if (x < 30) display.drawBitmap(125, 0, excelent, 8, 8, SSD1306_WHITE);
  }
}
