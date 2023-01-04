void obstacle() {
  if (mi2 - mi3 > 30) {
    sf = sonarf.ping_cm();
    mi3 = mi2;
  }
  if (sf < object_boundary && sf > 0) {
    head_light(1);
    braking_mechanism(1.5);
    motorSpeedR(6 * spl, 6 * spr);
    delay(turn);
    motorSpeedL(6 * spl, 6 * spr);
    delay(br);
    mos(4 * spl, 10 * spr);
    check();
    while (sum == 0) check();
    while (sum != 0) check();
    braking_mechanism(1);
    motorSpeedR(6 * spl, 6 * spr);
    check();
    while (sensor[2] == 0 && sensor[3] == 0) check();
    motorSpeedL(6 * spl, 6 * spr);
    delay(br);
    head_light(0);
  }
}
