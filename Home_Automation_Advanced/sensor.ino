void temp_check() {
  if (millis() - update_timer > 60000) {
    float t1 = dht1.readTemperature();
    float h1 = dht1.readHumidity();
    float t2 = dht2.readTemperature();
    float h2 = dht2.readHumidity();
    temperature1.updateAndReportParam("Temperature", t1);
    temperature2.updateAndReportParam("Temperature", h1);
    temperature3.updateAndReportParam("Temperature", t2);
    temperature4.updateAndReportParam("Temperature", h2);
    Serial.println(String(t1) + " " + String(h1) + " " + String(t2) + " " + String(h2));
    update_timer = millis();
  }
}