void home_screen() {
  lcd.setCursor(0, 0);
  lcd.print("   LoRa Based   ");
  lcd.setCursor(0, 1);
  lcd.print("   EV Charger   ");
}

void time_print(int a) {
  lcd.setCursor(10, 1);
  if (a < 10) lcd.print("    ");
  else if (a < 100) lcd.print("   ");
  else if (a < 1000) lcd.print("  ");
  else if (a < 10000) lcd.print(" ");
  lcd.print(a);
}