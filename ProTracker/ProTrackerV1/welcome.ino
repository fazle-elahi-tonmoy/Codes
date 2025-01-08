void welcome_screen() {
  tft.fillScreen(TFT_WHITE);
  tft.setFreeFont(FF6);
  tft.setTextColor(TFT_DARKGREY);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Welcome to", tft.width() / 2, 80);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_BLACK);
  tft.setFreeFont(FF7);
  tft.drawString("MZM Textile Ltd", 130, 150);
  drawImage(140, 230, 201, 41, skylark_201_41);
  drawImage(40, 120, 81, 91, MZM_81_91);
}