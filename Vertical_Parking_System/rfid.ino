short int rfid_read() {
  if (!rfid.PICC_IsNewCardPresent()) return 0;
  if (!rfid.PICC_ReadCardSerial()) return 0;
  for (byte i = 0; i < 4; i++) cardValue[i] = rfid.uid.uidByte[i];
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  byte card = card_verify();
  if (!card) {
    Serial.println("Wrong Card!");
    return -1;
  } else Serial.println("The Pass Number is: " + String(card));
  return card;
}

byte card_verify() {
  for (byte i = 0; i < 8; i++) {
    bool flag = 0;
    for (byte j = 0; j < 4; j++)
      if (pass[i][j] != cardValue[j]) {
        flag = 1;
        break;
      }
    if (!flag) return i + 1;
  }
  return 0;
}