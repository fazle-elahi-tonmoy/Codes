void unlock() {
  char key = keypad.getKey();
  if (key) {
    for (byte i = 1; i <= 3; i++) {
      pass_input[i - 1] = pass_input[i];
    }
    pass_input[3] = key;
    bool flag = 1;
    for (byte i = 0; i < 4; i++) {
      Serial.print(pass_input[i]);
      if (pass_input[i] != password[i]) flag = 0;
    }

    Serial.println();

    if (flag) {
      digitalWrite(8, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    UNLOCKED");
      delay(5000);
      digitalWrite(8, 0);
      start_screen();
      for (byte i = 0; i < 4; i++) pass_input[i] = 'A';
    }
  }
}