void error_screen() {
  tft.fillRect(90, 60, 300, 200, TFT_BLACK);
  tft.setTextColor(TFT_RED);
  tft.setTextDatum(BC_DATUM);
  tft.setFreeFont(FSSB24);
  tft.drawString("ERROR", 240, 160);
  tft.setTextDatum(TC_DATUM);
  tft.setFreeFont(FSSB9);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("No API Response", 240, 170);

  digitalWrite(API_FAIL_LED, 1);
  digitalWrite(buzzer, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
  digitalWrite(buzzer, 0);
  delay(250);
  digitalWrite(API_FAIL_LED, 1);
  digitalWrite(buzzer, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
  digitalWrite(buzzer, 0);
  delay(250);
  digitalWrite(API_FAIL_LED, 1);
  digitalWrite(buzzer, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
  digitalWrite(buzzer, 0);

  error_disp_mode = 1;
  error_disp_timer = millis();
}