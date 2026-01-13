bool rfid_read() {
  if (!rfid.PICC_IsNewCardPresent()) return 0;
  if (!rfid.PICC_ReadCardSerial()) return 0;
  for (byte i = 0; i < 4; i++) cardValue[i] = rfid.uid.uidByte[i];
  rfid_value = "";
  for (byte i = 0; i < 4; i++)
    rfid_value += String(cardValue[i]);
  Serial.println("Card Punched: " + rfid_value);
  display.clearDisplay();
  text("SCANNING..", 04, 25, 2);
  display.display();
  beep(1, 1);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return 1;
}

void rfid_check() {
  if (rfid_read()) {
    JsonObject response = sendPostRequest(rfid_value, vehicle_id, gps_location);
    if (response["message"] == "Log created successfully") {
      display.clearDisplay();
      //      Serial.println(response["message"]);
      String res = response["type"];
      Serial.println(res);
      text("CARD PUNCH", 04, 8, 2);
      (res == "Check In") ? text("  ENTRY  ", 11, 40, 2) : text("   EXIT   ", 04, 40, 2);
      display.display();
      beep(2, 1);
      delay(300);
    }

    else if (response["message"] == "Account balance is zero") {
      display.clearDisplay();
      text(" BALANCE ", 11, 8, 2);
      text("  EMPTY  ", 11, 40, 2);
      display.display();
      beep(3, 5);
    }

    else if (response["message"] == "Card is not registered") {
      display.clearDisplay();
      text("  WRONG  ", 11, 8, 2);
      text("   CARD   ", 04, 40, 2);
      display.display();
      beep(3, 5);
    }

    else {
      display.clearDisplay();
      text("CARD PUNCH", 04, 8, 2);
      text("  FAILED  ", 04, 40, 2);
      display.display();
      beep(3, 5);
    }
  }
}
