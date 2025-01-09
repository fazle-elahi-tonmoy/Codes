void sendHttpRequest() {
  String url = "http://163.47.84.201:9090/garments-pro/protracker/sewing-droplets/iot/" + String(WiFi.macAddress()) + "/summary";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String response = http.getString();
      Serial.println("_______________________________");
      Serial.println("Data sent successfully.");


      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        JsonObject data = doc["data"];
        machineMac = data["machine_mac"].as<const char*>();
        process = data["process"].as<const char*>();
        user = data["user"].as<const char*>();
        machineNo = data["machine_no"].as<const char*>();
        buyer = data["buyer"].as<const char*>();
        style = data["style"].as<const char*>();
        workingHour = data["working_hour"].as<const char*>();
        npt = data["npt"].as<const char*>();
        hourlyTarget = data["hourly_target"];
        hourlyAchievement = data["hourly_achievement"];
        dailyTarget = data["daily_target"];
        dailyAchievement = data["daily_achievement"];
        defectQuantity = data["defect_quantity"];
        cycleTime = data["cycle_time"];

        Serial.println("Extracted Data:");

        Serial.println("Machine MAC: " + machineMac);
        Serial.println("Process: " + process);
        Serial.println("User: " + user);
        Serial.println("Machine No: " + machineNo);
        Serial.println("Buyer: " + buyer);
        Serial.println("Style: " + style);
        Serial.println("Working Hour: " + workingHour);
        Serial.println("NPT: " + npt);
        Serial.println("Hourly Target: " + String(hourlyTarget));
        Serial.println("Hourly Achievement: " + String(hourlyAchievement));
        Serial.println("Daily Target: " + String(dailyTarget));
        Serial.println("Daily Achievement: " + String(dailyAchievement));
        Serial.println("Defect Quantity: " + String(defectQuantity));
        Serial.println("Cycle Time: " + String(cycleTime));
        Serial.println("_______________________________");

      }
    }

    else {
      Serial.println("Error code: " + String(httpResponseCode));
    }
    http.end();
  }
}