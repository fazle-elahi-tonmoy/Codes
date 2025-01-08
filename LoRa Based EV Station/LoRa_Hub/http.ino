String http_Req(String str_modes, String str_uid, String hub_id) {
  if (WiFi.status() == WL_CONNECTED) {
    String http_req_url = "";

    if (str_modes == "atc") {
      http_req_url = Web_App_URL + "?sts=atc";
      http_req_url += "&uid=" + str_uid;
      http_req_url += "&hid=" + hub_id;
    }
    if (str_modes == "reg") {
      http_req_url = Web_App_URL + "?sts=reg";
      http_req_url += "&uid=" + str_uid;
      http_req_url += "&hid=" + hub_id;
    }

    Serial.println();
    Serial.println("Sending request to Google Sheets...");
    Serial.println(http_req_url);

    HTTPClient http;
    http.begin(http_req_url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    Serial.print("HTTP Status Code : ");
    Serial.println(httpCode);

    String payload;
    if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Payload: " + payload);
    }
    http.end();

    String sts_Res = getValue(payload, ',', 0);
    String result = getValue(payload, ',', 1);
    if (sts_Res == "OK") {
      return result;
    }

    else {
      return "Error";
    }
  }

  else {
    return "Error";
  }
}