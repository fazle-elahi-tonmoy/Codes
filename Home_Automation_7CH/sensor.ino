void temp_check() {
  if (millis() - update_timer > 60000) {
    float t1 = dht1.readTemperature();
    float h1 = dht1.readHumidity();
    float t2 = dht2.readTemperature();
    float h2 = dht2.readHumidity();
    (isnan(t1)) ? Serial.println("Temperature Sensor 1 not Present") : temperature1.updateAndReportParam("Temperature", t1);
    (isnan(h1)) ? Serial.println("Humidity Sensor 1 not Present") : temperature2.updateAndReportParam("Temperature", h1);
    (isnan(t2)) ? Serial.println("Temperature Sensor 2 not Present") : temperature3.updateAndReportParam("Temperature", t2);
    (isnan(h2)) ? Serial.println("Humidity Sensor 2 not Present") : temperature4.updateAndReportParam("Temperature", h2);
    Serial.println(String(t1) + " " + String(h1) + " " + String(t2) + " " + String(h2));
    update_timer = millis();
  }
}

void trigger_check() {
  bool pir_flag = 0;
  bool ldr_flag = 0;
  for (byte i = 0; i < 3; i++)
    if (digitalRead(pir_pins[i])) pir_flag = 1;
  for (byte i = 0; i < 2; i++)
    if (digitalRead(ldr_pins[i])) ldr_flag = 1;

  if (security_check && (pir_flag || ldr_flag)) {
    Serial.println("Theft Alert!");
    trig.updateAndReportParam("Alarm Trigger", true);
    call_phone();
    security_check = 0;
    recheck_timer = millis();
  }

  if (!security_check && security_state && millis() - recheck_timer > 60000) {
    trig.updateAndReportParam("Alarm Trigger", false);
    security_check = 1;
  }
}