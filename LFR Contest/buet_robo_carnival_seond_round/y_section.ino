void y_section() {
  while (sum != 0) {
    check();
    mos(10 * spr, 10 * spl);
  }
  motorSpeedB(10 * spr, 10 * spl);
  brake = cl / d;
  delay(brake);
  check();
  while (bin != 12) {
    check();
    motorSpeedR(6 * spr, 6 * spl);
  }
  motorSpeedL(6 * spr, 6 * spl);
  delay(br);
  k30 = 0;
  k90 = 0;
  mov = 0;
  cl = base;
  brake = cl / d;
  k = 0;
}
