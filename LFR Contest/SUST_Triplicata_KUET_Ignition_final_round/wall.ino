void wall_follow() {
  head_light(1);
//  braking_mechanism(0.5);
  while (sum == 0) {
    check();
//    while (sonarleft() == 1);
//    while (sonarright() == 1);
//    sonarfront(2);
    mos(10 * spl, 10 * spr);
  }
  sl = sr = sf = 0;
  head_light(0);
  counter = 5;
}

int sonarleft() {
  check();
  if (sum != 0) return 0;
  sl = sonarl.ping_cm();
  if (sl < 30 && sl > 0) {
    sonarfront(1);
    error = midpoint - sl;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(8 * spl + error, 8 * spr - error);
    return 1;
  }
  else return 0;
}

int sonarright() {
  check();
  if (sum != 0) return 0;
  mi2 = millis();
  sr = sonarr.ping_cm();
  if (sr > 0 && sr < 30) {
    sonarfront(2);
    error = midpoint - sr;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(8 * spl - error, 8 * spr + error);
    return 1;
  }
  else return 0;
}

void sonarfront(int a) {
  mi2 = millis();
  sf = sonarf.ping_cm();
  if (sf < wall_boundary && sf > 0) {
    mos(-6 * spl, -6 * spr);
    delay(60);
    mos(0, 0);
    //    delay(100);
    (a == 2) ? motorSpeedL(6 * spl, 6 * spr) : motorSpeedR(6 * spl, 6 * spr);
    delay(300);
    (a == 1) ? motorSpeedL(6 * spl, 6 * spr) : motorSpeedR(6 * spl, 6 * spr);
    delay(br);
    mos(6 * spl, 6 * spr);
    sf = 0;
    sl = sr = midpoint;
  }
}


int wall_trigger(int a) {
  if (mi2 - mi3 >= 5) {
    (a==2)? sl = sonarl.ping_cm() : sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if((a == 2 && sl>0 && sl<30) || (a == 1 && sr>0 && sr<30)) return 1;
  else return 0;
}
