bool rfid_read() {
  if (!rfid.PICC_IsNewCardPresent()) return 0;
  if (!rfid.PICC_ReadCardSerial()) return 0;
  for (byte i = 0; i < 4; i++) cardValue[i] = rfid.uid.uidByte[i];
  rfid_value = "HUB_2:";
  for (byte i = 0; i < 4; i++) rfid_value += String(cardValue[i]);
  Serial.println("Card Punched: " + rfid_value);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return 1;
}