// ---------------- UI drawing (icons + layout) ----------------
void drawDefaultScreen() {
  dbg("[UI] drawDefaultScreen");
  tft.fillScreen(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_BLACK);
  tft.setFreeFont(FSB24);
  tft.drawString("Stationary", SCREEN_W / 2, SCREEN_H / 3 - 50, GFXFF);
  tft.drawString("Vending", SCREEN_W / 2, SCREEN_H / 3, GFXFF);
  tft.drawString("Machine", SCREEN_W / 2, SCREEN_H / 3 + 50, GFXFF);
  tft.setFreeFont(FSB18);
  tft.drawString("Please Punch Your ID Card", SCREEN_W / 2, (SCREEN_H * 3) / 4, GFXFF);
}

void drawProductSelectionScreen() {
  dbg("[UI] drawProductSelectionScreen");
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  // Header
  tft.setTextDatum(TL_DATUM);
  tft.drawString("User: " + userName, 10, 10, 4);
  tft.setTextDatum(TR_DATUM);
  tft.drawString("Balance: " + String(userBalance, 2), SCREEN_W - 10, 10, 4);

  // Layout: icons placed slightly lower/higher per your last instructions
  int iconY = SCREEN_H / 2 - 70;  // final vertical offset (you previously wanted ~50 lower than earlier; keep this)
  int spacing = (SCREEN_W - (4 * ICON_SIZE)) / 4;
  int x = spacing / 2;

  for (int i = 0; i < 4; i++) {
    const uint16_t *bmp = stapler_icon;
    if (strcmp(PRODUCT_NAMES[i], "Stapler") == 0) bmp = stapler_icon;
    else if (strcmp(PRODUCT_NAMES[i], "Pin") == 0) bmp = pin_icon;
    else if (strcmp(PRODUCT_NAMES[i], "Red Pen") == 0) bmp = redpen_icon;
    else if (strcmp(PRODUCT_NAMES[i], "Black Pen") == 0) bmp = blackpen_icon;

    // Draw icon and border
    tft.pushImage(x, iconY, ICON_SIZE, ICON_SIZE, bmp);
    tft.drawRect(x - 2, iconY - 2, ICON_SIZE + 4, ICON_SIZE + 4, TFT_DARKGREY);

    // Product name
    tft.setTextDatum(TC_DATUM);
    tft.drawString(PRODUCT_NAMES[i], x + ICON_SIZE / 2, iconY + ICON_SIZE + 20, 4);

    // Buttons (-, count, +)
    int btnW = 28, btnH = 28;
    int countY = iconY + ICON_SIZE + 50;
    int minusX = x - 35;
    int countX = x + (ICON_SIZE / 2) - (btnW / 2);
    int plusX = x + ICON_SIZE + 8;

    // Draw minus, count, plus boxes
    tft.drawRoundRect(minusX, countY, btnW, btnH, 5, TFT_DARKGREY);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("-", minusX + btnW / 2, countY + btnH / 2, 4);

    tft.drawRoundRect(countX, countY, btnW, btnH, 5, TFT_DARKGREY);
    tft.drawString(String(selectedQty[i]), countX + btnW / 2, countY + btnH / 2, 4);

    tft.drawRoundRect(plusX, countY, btnW, btnH, 5, TFT_DARKGREY);
    tft.drawString("+", plusX + btnW / 2, countY + btnH / 2, 4);

    // store positions? we will recompute positions in touch handler to remain consistent
    x += ICON_SIZE + spacing;
  }

  // Bottom total + action buttons
  float total = 0;
  for (int i = 0; i < 4; i++) total += selectedQty[i] * products[i].price;

  tft.setTextDatum(MC_DATUM);
  tft.drawString("Estimated: " + String(total, 2), SCREEN_W / 2, SCREEN_H - 48, 4);

  tft.fillRoundRect(20, SCREEN_H - 40, 110, 32, 6, TFT_RED);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Cancel", 75, SCREEN_H - 24, 4);
  tft.fillRoundRect(SCREEN_W - 130, SCREEN_H - 40, 110, 32, 6, TFT_GREEN);
  tft.drawString("OK", SCREEN_W - 75, SCREEN_H - 24, 4);
}