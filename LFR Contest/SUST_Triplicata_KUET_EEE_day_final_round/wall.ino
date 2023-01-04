void wall_follow() {
  braking_mechanism(0.5);
  digitalWrite(d30, HIGH);
  digitalWrite(d90, HIGH);
  m81 = 0;
  while (sum == 0) {
    check();
    mi3 = 0;
    while (sonarleft() == 1) sonarfront();
    mi3 = 0;
    while (sonarright() == 1) sonarfront();
    sonarfront();
    mos(125, 115);
  }
  sl = sr = sf = 0;
  counter = 7;
  digitalWrite(d30, LOW);
  digitalWrite(d90, LOW);
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
    error = midpoint - sl;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(125 + error, 115 - error);
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
    error = midpoint - sr;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(125 - error, 115 + error);
    return 1;
  }
  else return 0;
}

void sonarfront() {
  if (mi2 - m81 >= 5) {
    sf = sonarf.ping_cm();
    m81 = mi2;
  }
  if (sf < boundary && sf > 0) {
    mos(-6 * spl, -6 * spr);
    delay(40);
    motorSpeedL(6 * spl, 6 * spr);
    delay(turn);
    motorSpeedR(6 * spl, 6 * spr);
    delay(br);
    mos(5 * spl, 5 * spr);
    sf = 0;
    sl = sr = midpoint;
    m81=mi2=millis();
  }
}
