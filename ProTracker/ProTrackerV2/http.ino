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
        String machineMac = data["machine_mac"];
        String process = data["process"];
        String user = data["user"];
        String machineNo = data["machine_no"];
        String buyer = data["buyer"];
        String style = data["style"];
        String workingHour = data["working_hour"];
        String npt = data["npt"];
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

        // tft.setTextSize(1);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setFreeFont(FSS9);
        tft.drawString(user, 100, 38);
        tft.drawString(process, 100, 66);
        tft.drawString(buyer, 100, 94);
        tft.drawString(workingHour, 100, 122);
        tft.drawString(style, 350, 66);
        tft.drawString(npt, 350, 94);
        tft.drawString(machineNo, 350, 122);
        tft.setFreeFont(FSSB9);
        tft.drawString(String(hourlyTarget), 100, 190);
        tft.drawString(String(hourlyAchievement), 345, 190);
        tft.drawString(String(dailyTarget), 50, 275);
        tft.drawString(String(dailyAchievement), 160, 275);
        tft.drawString(String(defectQuantity), 290, 275);
        tft.drawString(String(cycleTime), 400, 275);
      }
    }

    else {
      Serial.println("Error code: " + String(httpResponseCode));
    }
    http.end();
  }
}