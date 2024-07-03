void reset_protocol() {
  if (digitalRead(gpio_0) == LOW) {  // Push button pressed
    delay(100);
    int startTime = millis();
    while (digitalRead(gpio_0) == LOW) {
      delay(1000);
      Serial.print(".  ");
    }
    Serial.println();
    int endTime = millis();
    if ((endTime - startTime) > 5000) {
      Serial.printf("Reset to factory.\n");
      RMakerFactoryReset(5);
    } else if ((endTime - startTime) > 3000) {
      Serial.printf("Reset Wi-Fi.\n");
      RMakerWiFiReset(5);
    }
  }
}