void y_section() {
  while (sum != 0 && sum != 6) check();
  if (sum == 0) {
    braking_mechanism(1.5);
    motorSpeedL(6 * spl, 6 * spr);
    while (sensor[2] == 0 && sensor[3] == 0) check();
    motorSpeedL(6 * spl, 6 * spr);
    delay(br);
    mos(6 * spl, 6 * spr);
  }
}
