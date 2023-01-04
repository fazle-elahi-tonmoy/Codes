void obstacle() {
  if (mi2 - mi3 > 5) {
    sf = sonarf.ping_cm();
    mi3 = mi2;
  }
  if (sf < boundary && sf > 0) {
    braking_mechanism(1.5);
    motorSpeedL(6 * spl, 6 * spr);
    delay(225);
    motorSpeedR(6 * spl, 6 * spr);
    delay(br);
    mos(10 * spl, 5 * spr);
    check();
    while (sensor[0] == 0){
      check();
      if(cl<peak) cl++;
    }
    //    while(1);
    braking_mechanism(0.5);
    motorSpeedL(6 * spl, 6 * spr);
    check();
    while (sensor[2] == 0 && sensor[3] == 0) check();
    motorSpeedR(6 * spl, 6 * spr);
    delay(br);
  }
  counter = 8;
}
