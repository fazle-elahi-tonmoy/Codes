void sendSMS(String phoneNumber, String message) {
  if (millis() - sms_timer > 500) {
    sms_timer = millis();
    if (stage == 1) SerialAT.println("AT+CMGS=\"" + phoneNumber + "\"");
    else if (stage == 2) SerialAT.print(message);
    else if (stage == 3) SerialAT.write(26);
    else {
      Serial.println("Message Sent!");
      stage = 0;
      digitalWrite(green, 0);
      return;
    }
    stage++;
  }
}