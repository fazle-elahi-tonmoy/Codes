void reset_protocol() {
  if (digitalRead(0) == LOW) {  // Push button pressed
    // Key debounce handling
    delay(100);
    int startTime = millis();
    while (digitalRead(0) == LOW) {
      delay(50);
    }
    int endTime = millis();
    if ((endTime - startTime) > 5000) {
      Serial.printf("Reset to factory.n");
      RMakerFactoryReset(2);
    }

    else if ((endTime - startTime) > 2000) {
      Serial.printf("Reset Wi-Fi.n");
      RMakerWiFiReset(2);
    }
  }
}