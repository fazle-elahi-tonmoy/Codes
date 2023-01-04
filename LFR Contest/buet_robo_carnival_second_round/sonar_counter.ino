void left_count() {
  display.setTextSize(9);
  display.clearDisplay();
  text("L", 40, 0);
  display.display();
  display.setTextSize(2);
  counter = 2;
  EEPROM.write(scount + 11, 2);
  delay(10);
  side[scount] = 2;
  scount++;

  digitalWrite(d90, HIGH);
  while (sensor[2] == 1 || sensor[3] == 1) {
    check();
    motorSpeedR(6 * spr, 6 * spl);
  }
  while (bin != 12) {
    check();
    motorSpeedR(6 * spr, 6 * spl);
  }
  motorSpeedL(6 * spr, 6 * spl);
  delay(br);
  digitalWrite(d90, LOW);
}

void right_count() {
  display.setTextSize(9);
  display.clearDisplay();
  text("R", 40, 0);
  display.display();
  display.setTextSize(2);
  counter = 2;
  EEPROM.write(scount + 11, 1);
  delay(10);
  side[scount] = 1;
  scount++;
  digitalWrite(d90, HIGH);
  while (sensor[2] == 1 || sensor[3] == 1) {
    check();
    motorSpeedR(6 * spr, 6 * spl);
  }
  while (bin != 12) {
    check();
    motorSpeedR(6 * spr, 6 * spl);
  }
  motorSpeedL(6 * spr, 6 * spl);
  delay(br);
  digitalWrite(d90, LOW);
}

