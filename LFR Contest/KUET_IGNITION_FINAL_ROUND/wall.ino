void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (sum == 0) {
//    sonar();
    check();
    //    if (sl <= midpoint - 2 && sl > 5) mos(0, 150);
    //    else if (sl >= midpoint + 2 && sl <= 30) mos(150, 0);
    //    else if (sr <= midpoint - 2 && sr > 5) mos(150, 0);
    //    else if (sr >= midpoint + 2 && sr <= 30) mos(0, 150);
    //    else mos(5 * spr, 5 * spl);
    mos(5 * spr, 4.5 * spl);
  }
  counter = 5;
  digitalWrite(calout, LOW);
}

int wall_trigger(int a) {
  if (mi2 - mi3 >= 5) {
    (a == 2) ? sl = sonarl.ping_cm() : sr = sonarr.ping_cm();
    mi3 = mi2;
  }
  if ((a == 2 && sl > 5 && sl < 25) || (a == 1 && sr > 5 && sr < 25)) return 1;
  else return 0;
}
