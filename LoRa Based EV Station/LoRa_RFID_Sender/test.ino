void system_test() {
    lcd.setCursor(0, 0);
    lcd.print("  Test System   ");
    lcd.setCursor(0, 1);
    lcd.print("     ACTIVE     ");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("   Relay Test   ");
    lcd.setCursor(0, 1);
    lcd.print("    Turned ON   ");
    digitalWrite(relay, 0);
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("   Relay Test   ");
    lcd.setCursor(0, 1);
    lcd.print("   Turned OFF   ");
    digitalWrite(relay, 1);
    delay(3000);
    LoRa.beginPacket();
    LoRa.print("LoRa:Test!");
    LoRa.endPacket();
    lcd.setCursor(0, 0);
    lcd.print("  LoRa Packet   ");
    lcd.setCursor(0, 1);
    lcd.print("      Sent      ");
    delay(3000);
    home_screen();
}