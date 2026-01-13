DynamicJsonDocument createPutJson(const String &gps_location){
  DynamicJsonDocument doc(128);
  doc["gps_location"] = gps_location;
  return doc;
}

DynamicJsonDocument createPostJson(const String &card_id, const String &vehicle_id, const String &gps_location){
  DynamicJsonDocument doc(256);
  doc["card_id"] = card_id;
  doc["vehicle_id"] = vehicle_id;
  doc["gps_location"] = gps_location;
  return doc;
}

JsonObject sendPutRequest(const String &vehicle_id, const String &gps_location)
{
  String serverUrl = "https://frontech.onrender.com/vehicles/" + vehicle_id;
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument jsonDoc = createPutJson(gps_location);
  String jsonData;
  serializeJson(jsonDoc, jsonData);

  Serial.println("Sending PUT request with JSON data: " + jsonData);

  int httpResponseCode = http.PUT(jsonData);

  if (httpResponseCode > 0)
  {
    String response = http.getString();

    // Parse the response JSON
    DynamicJsonDocument responseDoc(256);
    deserializeJson(responseDoc, response);

    http.end();
    return responseDoc.as<JsonObject>();
  }
  else
  {
    Serial.print("Error on sending PUT request. HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return JsonObject();
  }
}

JsonObject sendPostRequest(const String &card_id, const String &vehicle_id, const String &gps_location)
{
  String serverUrl = "https://frontech.onrender.com/logs/";
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument jsonDoc = createPostJson(card_id, vehicle_id, gps_location);
  String jsonData;
  serializeJson(jsonDoc, jsonData);

  Serial.println("Sending POST request with JSON data: " + jsonData);

  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode > 0)
  {
    String response = http.getString();

    // Parse the response JSON
    DynamicJsonDocument responseDoc(256);
    deserializeJson(responseDoc, response);

    http.end();
    return responseDoc.as<JsonObject>();
  }
  else
  {
    Serial.print("Error on sending POST request. HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return JsonObject();
  }
}
