// ---------------- Touch helpers ----------------
// Determine which UI element was touched. Returns codes:
// - 0..3 = minus button for product i
// - 20..23 = plus button for product i
// - 100 = Cancel
// - 101 = OK
// - -1 = none
int getTouchedElement(uint16_t sx, uint16_t sy) {
  int iconY = SCREEN_H / 2 - 70;
  int spacing = (SCREEN_W - (4 * ICON_SIZE)) / 4;
  int x = spacing / 2;
  for (int i = 0; i < 4; i++) {
    int btnW = 28, btnH = 28;
    int countY = iconY + ICON_SIZE + 50;
    int minusX = x - 35;
    int countX = x + (ICON_SIZE / 2) - (btnW / 2);
    int plusX = x + ICON_SIZE + 8;

    // minus
    if (sx >= (uint16_t)minusX && sx <= (uint16_t)(minusX + btnW) && sy >= (uint16_t)countY && sy <= (uint16_t)(countY + btnH)) return i;
    // plus
    if (sx >= (uint16_t)plusX && sx <= (uint16_t)(plusX + btnW) && sy >= (uint16_t)countY && sy <= (uint16_t)(countY + btnH)) return 20 + i;
    x += ICON_SIZE + spacing;
  }

  // Cancel
  if (sx >= 20 && sx <= 20 + 110 && sy >= SCREEN_H - 40 && sy <= SCREEN_H - 40 + 32) return 100;
  // OK
  if (sx >= SCREEN_W - 130 && sx <= SCREEN_W - 130 + 110 && sy >= SCREEN_H - 40 && sy <= SCREEN_H - 40 + 32) return 101;

  return -1;
}