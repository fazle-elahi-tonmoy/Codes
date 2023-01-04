void wall_follow() {
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  while (sum == 0) {
    check();
    while (sonarleft() == 1);
    while (sonarright() == 1);
    sonarfront();
    mos(8 * spr, 8 * spl);
  }
  sl = sr = sf = 0;
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
}

int sonarleft() {
  check();
  if (sum != 0) return 0;
  sl = sonarl.ping_cm();
  if (sl < 30 && sl > 0) {
    sonarfront();
    error = midpoint - sl;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(8 * spr - error, 8 * spl + error);
    return 1;
  }
  else return 0;
}

int sonarright() {
  check();
  if (sum != 0) return 0;
  sr = sonarr.ping_cm();
  if (sr > 0 && sr < 30) {
    sonarfront();
    error = midpoint - sr;
    error = constrain(error, -5, 5);
    error = error * wallp;
    mos(8 * spr + error, 8 * spl - error);
    return 1;
  }
  else return 0;
}

void sonarfront() {
  if (sum != 0) return;
  sf = sonarf.ping_cm();
  if (sf < wall_boundary && sf > 5) {
    sonar();
    digitalWrite(green, HIGH);
    mos(-8 * spr, -8 * spl);
    delay(100);
    (sl <= 30 && sl >= 5) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
    delay(turn);
    (sl <= 30 && sl >= 5) ? motorSpeedL(6 * spr, 6 * spl) : motorSpeedR(6 * spr, 6 * spl);
    delay(50);
    mos(8 * spr, 8 * spl);
    sf = 0;
    sl = sr = midpoint;
    digitalWrite(green, LOW);
  }
}


int wall_trigger(int a) {
  if (mi2 - mi3 >= 10) {
    (a == 2) ? sl = sonarl.ping_cm() : sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if ((a == 2 && sl > 0 && sl < 25) || (a == 1 && sr > 0 && sr < 25)) return 1;
  else return 0;
}
