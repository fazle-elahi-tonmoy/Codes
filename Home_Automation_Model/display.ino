void display_refresh() {
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" G   T  H  F L A");
  lcd.setCursor(0, 1);
  if (gas_value < 1000) lcd.print(" ");
  lcd.print(gas_value);
  if (gas_value < 100) lcd.print(" ");
  if (gas_value < 10) lcd.print(" ");
  lcd.print(" ");
  lcd.print(temp);
  if (temp < 10) lcd.print(" ");
  lcd.print(" ");
  lcd.print(hum);
  if (hum < 10) lcd.print(" ");
  lcd.print(" ");
  (fan_state) ? lcd.print(fan_speed / 50) : lcd.print("0");
  lcd.print(" ");
  lcd.print(bulb_auto);
  lcd.print(" ");
  lcd.print(theft_alarm);
}