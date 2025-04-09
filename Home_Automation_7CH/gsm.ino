void sms_prep() {
  if (step) {
    if (millis() - prep_time > 60000 && step == 1) {
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

void sendSMS() {
  if (millis() - sms_timer > 1000) {
    sms_timer = millis();
    if (stage == 1) Serial2.println("AT+CMGS=\"+88" + String(phone_number) + "\"");
    else if (stage == 2) Serial2.print(incoming_message);
    else if (stage == 3) Serial2.write(26);
    else {
      stage = 0;
      return;
    }
    stage++;
  }
}

void call_phone() {
  Serial2.println("ATD+ +88" + String(phone_number) + ";");
}