void welcome_screen() {
  tft.fillScreen(TFT_WHITE);
  tft.setFreeFont(FF6);
  tft.setTextColor(TFT_DARKGREY);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Welcome to", tft.width() / 2, 80);
  tft.setTextDatum(ML_DATUM);
  tft.setTextColor(TFT_BLACK);
  tft.setFreeFont(FSSB24);
  tft.drawString("MZM Textile Ltd", 105, 165);
  drawImage(140, 230, 201, 41, skylark_201_41);
  drawImage(15, 120, 80, 90, MZM_80x90);
}
