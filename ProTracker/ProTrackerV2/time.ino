void printLocalTime() {
  tft.fillRect(330, 0, 150, 30, TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.setTextDatum(TR_DATUM);
  tft.setFreeFont(FSS12);
  if (getLocalTime(&timeinfo)) {
    char timeString[10];
    strftime(timeString, 10, "%I:%M:%S", &timeinfo);
    tft.drawString(timeString, 470, 5);
  }
}