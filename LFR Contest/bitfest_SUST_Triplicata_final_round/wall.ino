void wall_follow() {
  braking_mechanism(1);
  while (sum == 0) {
    check();
    mi3 = 0;
    while (sonarleft() == 1);
    mi3 = 0;
    while (sonarright() == 1);
    mos(8 * spl, 8 * spr);
  }
  sl = sr = sf = 0;
  counter = 6;
}

int sonarleft() {
  check();
  if (sum != 0) return 0;
  mi2 = millis();
  if (mi2 - mi3 >= 5) {
    sl = sonarl.ping_cm();
    mi3 = mi2;
  }
  if (sl < 30 && sl > 0) {
    //    sonarfront();
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
  if (mi2 - mi3 >= 5) {
    sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if (sr > 0 && sr < 30) {
    //    sonarfront();
    error = midpoint - sr;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(8 * spl - error, 8 * spr + error);
    return 1;
  }
  else return 0;
}

//void sonarfront() {
//  mi2 = millis();
//  if (mi2 - mi1 >= 10) {
//    sonarfront();
//    mi1 = mi2;
//  }
//  if (sf < boundary && sf > 5) {
//    mos(-6*spl, -6*spr);
//    delay(40);
//    motorSpeedL(6 * spl, 6 * spr);
//    delay(turn);
//    motorSpeedR(6 * spl, 6 * spr);
//    delay(br);
//    mos(6*spl, 6*spr);
//    sf = 0;
//    sl = sr = midpoint;
//  }
//}
