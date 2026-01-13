// ---------------- WiFi + HTTP helpers ----------------
bool httpGetJson(const String &url, String &out) {
  if (WiFi.status() != WL_CONNECTED) {
    dbg("[HTTP] WiFi not connected!");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("NO WiFi!", SCREEN_W / 2, SCREEN_H / 2, 4);
    delay(2000);
    return false;
  }
  dbg("[HTTP] GET: " + url);
  HTTPClient http;
  http.setTimeout(20000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(url.c_str());
  int httpCode = http.GET();
  dbg("[HTTP] Status Code: " + String(httpCode));
  if (httpCode <= 0) {
    dbg("[HTTP] GET failed: " + String(http.errorToString(httpCode)));
    http.end();
    return false;
  }
  out = http.getString();
  dbg("[HTTP] Payload length: " + String(out.length()));
  // debug raw payload if small
  if (out.length() < 512) dbg("[HTTP] Payload: " + out);
  http.end();
  return true;
}

// Improved POST helper that follows redirect location and re-posts JSON payload
String cachedRedirect = "";  // global cache for the real script.googleusercontent URL

bool httpPostJson(const String &url, const String &payload, String &response) {
  if (WiFi.status() != WL_CONNECTED) {
    dbg("[HTTP] WiFi not connected (POST)!");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("NO WiFi!", SCREEN_W / 2, SCREEN_H / 2, 4);
    delay(2000);
    return false;
  }

  dbg("[HTTP] POST -> " + url);
  dbg("[HTTP] Payload: " + payload);

  HTTPClient http;
  http.setTimeout(20000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  // try strict follow first
  http.begin(url.c_str());
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);
  dbg("[HTTP] POST code: " + String(httpCode));

  // If we got a redirect-like code (301/302/303/307) we will try to follow the Location header manually
  if (httpCode == 301 || httpCode == 302 || httpCode == 303 || httpCode == 307) {
    String loc = http.getLocation();  // may be empty
    dbg("[HTTP] Redirect detected. Location: " + loc);
    http.end();
    if (loc.length() > 0 && (loc.startsWith("http://") || loc.startsWith("https://"))) {
      dbg("[HTTP] Re-posting to redirected location...");
      HTTPClient http2;
      http2.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      http2.begin(loc.c_str());
      http2.addHeader("Content-Type", "application/json");
      int code2 = http2.POST(payload);
      dbg("[HTTP] POST to redirected URL code: " + String(code2));
      if (code2 > 0) {
        response = http2.getString();
        dbg("[HTTP] POST redirected response length: " + String(response.length()));
        if (response.length() < 512) dbg("[HTTP] POST redirected response: " + response);
      }

      else {
        dbg("[HTTP] POST to redirected URL failed: " + String(http2.errorToString(code2)));
        http2.end();
        return false;
      }
      http2.end();
      return (httpCode > 0);  // response filled
    }

    else {
      dbg("[HTTP] No valid Location header to follow");
      return false;
    }
  }

  // Normal (non-redirect) response handling
  if (httpCode <= 0) {
    dbg("[HTTP] POST failed: " + String(http.errorToString(httpCode)));
    http.end();
    return false;
  }

  response = http.getString();
  dbg("[HTTP] POST response length: " + String(response.length()));
  if (response.length() < 512) dbg("[HTTP] POST response: " + response);
  http.end();
  return true;
}
