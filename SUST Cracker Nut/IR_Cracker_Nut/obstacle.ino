void obstacle(int a) {
  if (mi2 - mi4 > 30) {
    sf = sonarf.ping_cm();
    mi3 = mi2;
  }
  if (sf < object_boundary && sf > 10) {
    braking_mechanism();
    (a == 1) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
    delay(turn);
    (a == 2) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
    delay(br);
    (a == 1) ? mos(10 * spr, 3.5 * spl) : mos(3.5 * spr, 10 * spl);
    check();
    while (sum == 0) check();
    while (sum != 0) check();
    braking_mechanism();
    (a == 1) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
    check();
    while (sensor[2] == 0 && sensor[3] == 0) check();
    (a == 2) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
    delay(br);
  }
}
