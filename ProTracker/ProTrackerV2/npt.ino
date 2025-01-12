void npt_screen() {
  digitalWrite(NPT_LED, 1);
  digitalWrite(active_LED, 0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setFreeFont(FSSB9);
  tft.setTextDatum(MR_DATUM);
  tft.drawString("User:", 85, 45);
  tft.fillRoundRect(90, 35, 335, 24, 10, TFT_WHITE);
  tft.drawString("Buyer:", 85, 73);
  tft.fillRoundRect(90, 63, 335, 24, 10, TFT_WHITE);
  tft.drawString("Style:", 85, 101);
  tft.fillRoundRect(90, 91, 335, 24, 10, TFT_WHITE);
  tft.drawString("Machine NO:", 120, 129);
  tft.fillRoundRect(125, 119, 300, 24, 10, TFT_WHITE);
  tft.fillRoundRect(150, 160, 180, 50, 20, TFT_DARKGREY);
  tft.fillCircle(285, 185, 20, TFT_RED);
  tft.setTextColor(TFT_RED);
  tft.setFreeFont(FSSB18);
  tft.drawString("NPT", 255, 185);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.setFreeFont(FSS9);
  tft.drawString("NPT Activated", 240, 220);
  tft.drawString("Device is not working right now", 240, 245);
  tft.setTextDatum(BR_DATUM);
  tft.drawString("Please Contact with Supervisor", 470, 310);

  tft.setTextDatum(TL_DATUM);
  tft.setTextFont(1);
  tft.setCursor(10, 300);
  tft.print(String(WiFi.macAddress()));

  tft.setTextColor(TFT_BLACK);
  tft.setFreeFont(FSS9);
  tft.drawString(user, 100, 38);
  tft.drawString(buyer, 100, 66);
  tft.drawString(style, 100, 94);
  tft.drawString(machineNo, 135, 122);
}