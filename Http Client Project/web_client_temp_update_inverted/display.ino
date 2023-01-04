void text(String t, int x, int y) {
  display.setCursor(x, y);
  display.print(t);
}

void signal_strength() {
  int x = WiFi.RSSI();
  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print(WiFi.localIP());
  text("HTTP Code: " + String(http.GET()), 0, 36);
  display.drawBitmap(103, 54, network, 8, 8, SSD1306_WHITE);
  if (x == 0 || x > 100) display.drawBitmap(113, 54, no_signal, 8, 8, SSD1306_WHITE);
  else {
    if (x < 100) display.drawBitmap(113, 54, bad, 8, 8, SSD1306_WHITE);
    if (x < 50) display.drawBitmap(117, 54, medium, 8, 8, SSD1306_WHITE);
    if (x < 40) display.drawBitmap(121, 54, good, 8, 8, SSD1306_WHITE);
    if (x < 30) display.drawBitmap(125, 54, excelent, 8, 8, SSD1306_WHITE);
  }

}

void disp_update() {
  display.clearDisplay();
  signal_strength();
  display.setTextSize(3);
  text(String(p_temp) + " " +  + "C", 0, 0);
  display.drawBitmap(95, 0, degree, 8, 8, SSD1306_WHITE);
  display.display();
}
