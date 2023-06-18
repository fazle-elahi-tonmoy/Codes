void text(String t, byte x, byte y) {
  lcd.setCursor(x, y);
  lcd.print(t);
}

void starting_screen() {
  text("VAC:", 0, 0);
  for (byte i = 0; i < 8; i++) {
    lcd.print(" ");
    (vacancy[i]) ? lcd.print(i + 1) : lcd.print(" ");
  }
  clean(1);
  clean(3);
  text("   Punch Any Card   ", 0, 2);
  lcd.setCursor(current_slot * 2 + 3, 0);
}

void amount_display() {
  lcd.noBlink();

  int amount[8];
  for (byte i = 0; i < 8; i++) amount[i] = EEPROM.read(i + 8) * 50;

  lcd.clear();

  for (byte i = 0; i < 4; i++) {
    text(String(2 * i + 1) + ": " + String(amount[2 * i]), 0, i);
    text(String(2 * (i + 1)) + ": " + String(amount[2 * i + 1]), 10, i);
  }

  while (!push(button))
    ;
  lcd.clear();

  text("Total Collected Bill", 0, 0);
  uint32_t sum = 0;
  for (byte i = 0; i < 8; i++) sum += amount[i];
  lcd.setCursor(0, 2);
  if (sum < 100) lcd.print("         ");
  else if (sum < 1000) lcd.print("        ");
  else if (sum < 10000) lcd.print("        ");
  else if (sum < 100000) lcd.print("       ");
  else if (sum < 1000000) lcd.print("       ");
  else if (sum < 10000000) lcd.print("      ");
  else if (sum < 100000000) lcd.print("      ");
  else if (sum < 1000000000) lcd.print("     ");
  else if (sum < 10000000000) lcd.print("     ");
  else if (sum < 100000000000) lcd.print("    ");
  else if (sum < 1000000000000) lcd.print("    ");
  else if (sum < 10000000000000) lcd.print("   ");
  else if (sum < 100000000000000) lcd.print("   ");
  else if (sum < 1000000000000000) lcd.print("  ");
  else if (sum < 10000000000000000) lcd.print("  ");
  lcd.print(sum);
  text("        Taka", 0, 3);



  while (1) {
    int press = push(button);
    if (press == 1) break;
    else if (press == 2) {
      for (byte i = 0; i < 8; i++) {
        EEPROM.write(i + 8, 0);
        delay(10);
      }
      break;
    }
  }
  lcd.blink();

  starting_screen();
}

void clean(byte a) {
  text("                    ", 0, a);
}