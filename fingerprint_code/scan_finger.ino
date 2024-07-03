void getFingerprintID() {
  uint8_t p = finger.getImage();

  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      // Serial.println("No finger detected");
      return;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not convert image");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a match!");
    digitalWrite(relay, 0);
    digitalWrite(blue, 1);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(relay, 1);
    digitalWrite(blue, 0);
  } else {
    digitalWrite(red, 1);
    digitalWrite(buzzer,1);
    Serial.println("No match found");
    delay(1000);
    digitalWrite(red, 0);
    digitalWrite(buzzer,0);
  }
}
