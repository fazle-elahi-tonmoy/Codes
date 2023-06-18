void rotation(byte a) {
  if (current_slot != verify) digitalWrite(relay, 0);
  while (current_slot != verify) {
    while (sensor_read(platform_sensor, 1))
      ;
    while (sensor_read(platform_sensor, 0))
      ;
    current_slot++;
    if (current_slot > 8) current_slot = 1;
    lcd.setCursor(current_slot * 2 + 3, 0);
  }
  delay(rotation_adjustment);
  digitalWrite(relay, 1);
  (vacancy[a - 1]) ? text("Insert Your Car Here", 0, 2) : text("Take Out Your Car...", 0, 2);
  lcd.setCursor(current_slot * 2 + 3, 0);
  if (vacancy[a - 1]) {
    while (sensor_read(side_sensor, 1))
      ;
    while (sensor_read(front_sensor, 0))
      ;
  }

  else {
    while (sensor_read(side_sensor, 0))
      ;
    while (sensor_read(front_sensor, 1))
      ;
  }
}