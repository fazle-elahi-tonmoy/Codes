void y_section() {
  while (sum != 0) {
    check();
    mos(10 * spr, 10 * spl);
  }
  motorSpeedB(250, 250);
  delay(brake);
  check();
  if (side == 1) {
    while (bin != 12) {
      check();
      motorSpeedR(6 * spr, 6 * spl);
    }
    motorSpeedL(6 * spr, 6 * spl);
    delay(4 * dt);
  }
  else if (side == 2) {
    while (bin != 12) {
      check();
      motorSpeedL(6 * spr, 6 * spl);
    }
    motorSpeedR(6 * spr, 6 * spl);
    delay(4 * dt);
  }
  cl = base;
  brake = cl / d;
  k = 0;
}
