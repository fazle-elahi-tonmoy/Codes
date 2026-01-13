bool verifyUID(const String &uid) {
  String url = String(WEBAPP_URL) + "?action=verify&uid=" + uid;
  String body;
  if (!httpGetJson(url, body)) {
    dbg("[HTTP] verify GET failed");
    return false;
  }

  // Try to parse JSON (trim potential wrappers)
  body.trim();
  int s = body.indexOf('{');
  int e = body.lastIndexOf('}');
  if (s >= 0 && e > s) body = body.substring(s, e + 1);
  else {
    dbg("[HTTP] Invalid response format: " + body);
    return false;
  }

  DynamicJsonDocument doc(2048);
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    dbg("[JSON] parse error (verify): " + String(err.c_str()));
    dbg("[RAW] " + body);
    return false;
  }
  if (!doc["ok"]) {
    dbg("[HTTP] verify ok=false");
    return false;
  }
  if (!doc["valid"]) {
    dbg("[RFID] card invalid");
    return false;
  }

  userUID = doc["user"]["uid"].as<String>();
  userName = doc["user"]["name"].as<String>();
  userBalance = (float)doc["user"]["balance"].as<double>();
  dbg("[USER] " + userName + " uid=" + userUID + " balance=" + String(userBalance, 2));
  return true;
}