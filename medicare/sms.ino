void sms_prep() {
  if (step) {
    if (millis() - prep_time > 10000 && step == 1) {
      prep_time = millis();
      Serial2.println("AT");
      step = 2;
    } 
    
    else if (millis() - prep_time > 1000 && step == 2) {
      Serial2.println("AT+CMGF=1");
      step = 0;
    }
  }
}

void sendSMS(String phoneNumber, String message) {
  if (millis() - sms_timer > 500) {
    Serial.printf("Stage %d: ", stage);
    sms_timer = millis();
    if (stage == 1) Serial2.println("AT+CMGS=\"" + phoneNumber + "\"");
    else if (stage == 2) Serial2.print(message);
    else if (stage == 3) Serial2.write(26);
    else {
      Serial.println("Message Sent!");
      stage = 0;
      return;
    }
    stage++;
  }
}

void call_phone(String phoneNumber){
  Serial2.println("ATD+" + phoneNumber +";");
}