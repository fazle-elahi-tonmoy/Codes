// ---------------- Server endpoints ----------------
bool getPricesFromServer() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Checking Stock", SCREEN_W / 2, SCREEN_H / 2, 4);
  String url = String(WEBAPP_URL) + "?action=prices";
  String body;
  if (!httpGetJson(url, body)) {
    dbg("[DATA] Failed to fetch prices");
    return false;
  }
  // parse JSON
  DynamicJsonDocument doc(4096);
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    dbg("[JSON] parse error (prices): " + String(err.c_str()));
    dbg("[RAW] " + body);
    return false;
  }
  if (!doc["ok"]) {
    dbg("[HTTP] prices returned ok=false");
    return false;
  }
  JsonObject prices = doc["prices"];
  for (int i = 0; i < 4; i++) {
    String k = PRODUCT_NAMES[i];
    products[i].name = k;
    products[i].price = prices[k]["price"] | 0.0;
    products[i].stock = prices[k]["stock"] | 0;
    products[i].timeMs = prices[k]["timeMs"] | 500;
    dbg("[DATA] " + String(k) + " price=" + String(products[i].price) + " stock=" + String(products[i].stock) + " timeMs=" + String(products[i].timeMs));
  }
  return true;
}