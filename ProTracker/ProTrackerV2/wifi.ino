void disp_wifi() {
  tft.fillScreen(TFT_WHITE);
  drawImage(190, 50, 101, 101, qr_101x101);
  tft.setTextColor(TFT_BLACK);
  tft.setFreeFont(FSSB18);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Connect to WiFi", tft.width() / 2, 250);
}
