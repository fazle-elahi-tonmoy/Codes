void main_screen_update(bool a) {
  digitalWrite(NPT_LED, 0);
  digitalWrite(active_LED, 1);
  if (a) {
    tft.fillScreen(TFT_WHITE);
    drawImage(159, 2, 162, 30, MZM_Textile_162x30);
    tft.setTextColor(TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
    tft.setTextFont(1);
    tft.setCursor(10, 10);
    tft.print(String(WiFi.macAddress()));

    tft.setFreeFont(FSSB9);
    tft.setTextDatum(MR_DATUM);
    tft.drawString("User:", 85, 45);
    tft.drawString("Process:", 85, 73);
    tft.drawString("Buyer:", 85, 101);
    tft.drawString("Work hr:", 85, 129);
    tft.drawString("Style:", 335, 73);
    tft.drawString("NPT:", 335, 101);
    tft.drawString("Machine NO:", 335, 129);
    //main green boxes
    tft.fillRect(10, 150, 225, 90, 0x04AD);
    tft.fillRect(245, 150, 225, 90, 0x04AD);
    tft.drawLine(60, 185, 185, 185, TFT_WHITE);
    tft.drawLine(275, 185, 440, 185, TFT_WHITE);
    //secondary blue boxes
    tft.fillRect(10, 245, 110, 65, 0x04B8);
    tft.fillRect(125, 245, 110, 65, 0x04B8);
    tft.fillRect(245, 245, 110, 65, 0x04B8);
    tft.fillRect(360, 245, 110, 65, 0x04B8);
    tft.setFreeFont(FSS9);
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Hourly Target", 123, 160);
    tft.drawString("Hourly Achievement", 357, 160);
    tft.drawString("Daily Target", 65, 249);
    tft.drawString("D.Achieve", 180, 249);
    tft.drawString("Defect QTY", 300, 249);
    tft.drawString("Cycle Time", 415, 249);
  }

  tft.fillRoundRect(90, 63, 180, 24, 10, TFT_WHITE);
  tft.drawRoundRect(90, 63, 180, 24, 10, TFT_BLACK);
  tft.fillRoundRect(90, 91, 180, 24, 10, TFT_WHITE);
  tft.drawRoundRect(90, 91, 180, 24, 10, TFT_BLACK);
  tft.fillRoundRect(90, 119, 100, 24, 10, TFT_WHITE);
  tft.drawRoundRect(90, 119, 100, 24, 10, TFT_BLACK);
  tft.fillRoundRect(340, 63, 120, 24, 10, TFT_WHITE);
  tft.drawRoundRect(340, 63, 120, 24, 10, TFT_BLACK);
  tft.fillRoundRect(340, 91, 120, 24, 10, TFT_WHITE);
  tft.drawRoundRect(340, 91, 120, 24, 10, TFT_BLACK);
  tft.fillRoundRect(340, 119, 120, 24, 10, TFT_WHITE);
  tft.drawRoundRect(340, 119, 120, 24, 10, TFT_BLACK);

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(TL_DATUM);
  tft.setFreeFont(FSS9);
  tft.drawString(user, 100, 38);
  tft.drawString(process, 100, 66);
  tft.drawString(buyer, 100, 94);
  tft.drawString(workingHour, 100, 122);
  tft.drawString(style, 350, 66);
  tft.drawString(npt, 350, 94);
  tft.drawString(machineNo, 350, 122);

  tft.fillRoundRect(60, 195, 125, 30, 10, TFT_WHITE);
  tft.fillRoundRect(295, 195, 125, 30, 10, TFT_WHITE);
  tft.fillRoundRect(20, 275, 90, 25, 10, TFT_WHITE);
  tft.fillRoundRect(135, 275, 90, 25, 10, TFT_WHITE);
  tft.fillRoundRect(255, 275, 90, 25, 10, TFT_WHITE);
  tft.fillRoundRect(370, 275, 90, 25, 10, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setFreeFont(FSSB9);
  tft.drawString(String(hourlyTarget), 120, 208);
  tft.drawString(String(hourlyAchievement), 357, 208);
  tft.drawString(String(dailyTarget), 65, 285);
  tft.drawString(String(dailyAchievement), 180, 285);
  tft.drawString(String(defectQuantity), 300, 285);
  tft.drawString(String(cycleTime), 415, 285);
}