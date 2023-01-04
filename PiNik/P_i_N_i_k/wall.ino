void wall_follow() {
  head_light(1);
  lfang.write(intl);
  rfang.write(intr);
  braking_mechanism(0.5);
  while (sum == 0) {
    check();
    while (sonarleft() == 1);
    while (sonarright() == 1);
    sonarfront(2);
    mos(150, 150);
  }
  sl = sr = sf = 0;
  head_light(0);
  counter ++;
  turn = 0;
  lfang.write(fl);
  rfang.write(fr);
}

byte sonarleft() {
  check();
  if (sum != 0) return 0;
  sl = sonarl.ping_cm();
  if (sl < 30 && sl > 0) {
    sonarfront(1);
    error = midpoint - sl;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(150 + error, 150 - error);
    return 1;
  }
  else return 0;
}

byte sonarright() {
  check();
  if (sum != 0) return 0;
  mi2 = millis();
  sr = sonarr.ping_cm();
  if (sr > 0 && sr < 30) {
    sonarfront(2);
    error = midpoint - sr;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(150 - error, 150 + error);
    return 1;
  }
  else return 0;
}

void sonarfront(byte a) {
  sf = sonarf.ping_cm();
  if (sf < wall_boundary && sf > 0) {
    mos(-150, -150);
    delay((peak + base) / (2 * d));
    (a == 2) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(rotation);
    (a == 1) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(br);
    mos(150, 150);
    sf = 0; sl = sr = midpoint;
  }
}


byte wall_trigger(byte a) {
  mi2 = millis();
  if (mi2 - mi3 >= 25) {
    (a == 2) ? sl = sonarl.ping_cm() : sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if ((a == 2 && sl > 5 && sl < midpoint + 10) || (a == 1 && sr > 5 && sr < midpoint + 10)) return 1;
  else return 0;
}
