void sendSummeryRequest() {
  String url = main_url + String(WiFi.macAddress()) + "/summary";

  if (WiFi.status() == WL_CONNECTED) {
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
        Serial.println("_______________________________");
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

void sendOKrequest() {
  String url = main_url + String(WiFi.macAddress()) + "/ok";


  if (WiFi.status() == WL_CONNECTED) {
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["status"] = "ok";

    String jsonPayload;
    serializeJson(jsonDoc, jsonPayload);
    int httpResponseCode = http.POST(jsonPayload);
    Serial.println(httpResponseCode);

    if (httpResponseCode == 200) {
      String response = http.getString();
      digitalWrite(API_OK_LED, 1);
      delay(100);
      digitalWrite(API_OK_LED, 0);
      sendSummeryRequest();
      main_screen_update(0);
      http.end();
      return;
    } else http.end();
  }
  digitalWrite(API_FAIL_LED, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
  delay(250);
  digitalWrite(API_FAIL_LED, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
  delay(250);
  digitalWrite(API_FAIL_LED, 1);
  delay(250);
  digitalWrite(API_FAIL_LED, 0);
}

void checkNPT() {
  String url = main_url + String(WiFi.macAddress()) + "/npt";

  if (WiFi.status() == WL_CONNECTED) {
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String response = http.getString();

      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        JsonObject data = doc["data"];
        machineMac = data["machine_mac"].as<const char*>();
        npt_status = data["npt_status"].as<const char*>();
        user = data["user"].as<const char*>();
        machineNo = data["machine_no"].as<const char*>();
        buyer = data["buyer"].as<const char*>();
        style = data["style"].as<const char*>();
        npt_start_time = data["start_time"].as<const char*>();

        if (npt_status == "ON" && npt_mode == 0) {
          npt_mode = 1;
          npt_screen();
        } else if (npt_status == "OFF" && npt_mode == 1) {
          npt_mode = 0;
          main_screen_update(1);
        }
      }
    }

    else {
      Serial.println("Error code: " + String(httpResponseCode));
    }
    http.end();
  }
}

bool sendData(String req) {
  String url = main_url + String(WiFi.macAddress()) + req;

  if (WiFi.status() == WL_CONNECTED) {
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String response = http.getString();
      http.end();
      return 1;
    }

    else {
      Serial.println("Error code: " + String(httpResponseCode));
      http.end();
      return 0;
    }
  }
  return 0;
}
