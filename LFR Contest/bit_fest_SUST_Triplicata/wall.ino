void wall_follow() {
  while (sum == 0) {
    check();
    mi3 = 0;
    while (sonarleft() == 1);
    mi3 = 0;
    while (sonarright() == 1);
    mos(6*spl, 6*spr);
  }
  sl=sr=sf=0;
  counter = 6;
}

int sonarleft() {
  mi2 = millis();
  if (mi2 - mi3 >= 5) {
    sl = sonarl.ping_cm();
    mi3 = mi2;
  }
  if (sl < 30 && sl > 0) {
//    sonarfront();
    error = midpoint - sl;
    error = constrain(error, -10, 10);
    error = error * wallp;
    mos(6*spl + error, 6*spr - error);
    return 1;
  }
  else return 0;
}

int sonarright() {
  mi2 = millis();
  if (mi2 - mi3 >= 5) {
    sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if (sr > 0 && sr < 30) {
//    sonarfront();
    error = midpoint - sr;
    error = constrain(error, -10, 10);
    error = error * wallp;
    mos(6*spl - error, 6*spr + error);
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
//    motorSpeedL(5 * spl, 5 * spr);
//    delay(turn);
//    motorSpeedR(5 * spl, 5 * spr);
//    delay(br);
//    mos(6*spl, 6*spr);
//    sf = 0;
//    sl = sr = midpoint;
//  }
//}
