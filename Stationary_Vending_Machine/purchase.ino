// Purchase: send {action: "purchase", uid, total, items: {name: qty, ...}}
bool postPurchaseAndUpdate(const String &uid, float total, JsonObject &items, DynamicJsonDocument &outDoc) {
  DynamicJsonDocument doc(1024);
  doc["action"] = "purchase";
  doc["uid"] = uid;
  doc["total"] = total;
  doc["items"] = items;
  String payload;
  serializeJson(doc, payload);
  String resp;
  if (!httpPostJson(String(WEBAPP_URL), payload, resp)) {
    dbg("[HTTP] purchase POST failed");
    return false;
  }
  // Attempt to parse response
  DeserializationError derr = deserializeJson(outDoc, resp);
  if (derr) {
    dbg("[JSON] parse error (purchase): " + String(derr.c_str()));
    dbg("[RAW] " + resp);
    return true;
  }

  if (!outDoc["ok"]) {
    dbg("[SERVER] purchase returned ok=false");
    return false;
  }

  dbg("[SERVER] purchase OK");
  return true;
}