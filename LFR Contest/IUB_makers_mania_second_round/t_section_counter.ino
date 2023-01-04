void counter_logic() {
  if (side == 2) {
    while (sum != 0) {
      check();
      mos(10 * spr, 10 * spl);
    }
    motorSpeedB(250, 250);
    delay(brake);
    while (bin != 3) {
      check();
      mos(-5 * spr , 8 * spl);
    }
    counter = 1;
    EEPROM.write(10, 1);
  }

  if (side ==  1) {
    while (sum != 0) {
      check();
      mos(10 * spr, 10 * spl);
    }
    motorSpeedB(250, 250);
    delay(brake * 3);
    while (bin != 48) {
      check();
      mos(8 * spr, -5*spl);
    }
    counter = 1;
    EEPROM.write(10, 1);
  }
  cl = base;
  brake = cl / d;
}
