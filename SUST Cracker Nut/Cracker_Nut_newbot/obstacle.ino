void obstacle(int a) {
  if (mi2 - mi4 > 30) {
    sf = sonarf.ping_cm();
    mi3 = mi2;
  }
  if (sf < object_boundary && sf > 10) {
    braking_mechanism();
    (a == 1) ? motorSpeedR(6 * sp, 6 * sp) : motorSpeedL(6 * sp, 6 * sp);
    delay(turn);
    (a == 2) ? motorSpeedR(6 * sp, 6 * sp) : motorSpeedL(6 * sp, 6 * sp);
    delay(br);
    (a == 1) ? mos(10 * sp, 3.5 * sp) : mos(3.5 * sp, 10 * sp);
    check();
    while (sum == 0) check();
    while (sum != 0) check();
    braking_mechanism();
    (a == 1) ? motorSpeedR(6 * sp, 6 * sp) : motorSpeedL(6 * sp, 6 * sp);
    check();
    while (sensor[2] == 0 && sensor[3] == 0) check();
    (a == 2) ? motorSpeedR(6 * sp, 6 * sp) : motorSpeedL(6 * sp, 6 * sp);
    delay(br);
  }
}
