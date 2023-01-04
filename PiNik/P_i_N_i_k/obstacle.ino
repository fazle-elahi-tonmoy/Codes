void  obstacle(short int a) {
  if (mi2 - mi4 > 30) {
    sf = sonarf.ping_cm();
    mi4 = mi2;
  }
  if (sf <= object_boundary && sf > 0) {
    head_light(1); lfang.write(intl); rfang.write(intr);
    braking_mechanism(1.5); mos(0, 0); delay(50);

    (a == 1) ? motorSpeedR(150, 150) : motorSpeedL(150, 150); delay(rotation);
    (a == 1) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(br);

    mos(10 * sp, 10 * sp); m82 = m81 = millis();
    while (m82 - m81 < o1) {
      m82 = millis(); if (cl < peak) cl++;
    }
    braking_mechanism(1); mos(0, 0); delay(50);

    (a == 1) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(rotation);
    (a == 1) ? motorSpeedR(150, 150) : motorSpeedL(150, 150); delay(br);

    mos(10 * sp, 10 * sp); m82 = m81 = millis();
    while (m82 - m81 < o2) {
      m82 = millis(); if (cl < peak) cl++;
    }
    braking_mechanism(1); mos(0, 0); delay(50);

    (a == 1) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(rotation);
    (a == 1) ? motorSpeedR(150, 150) : motorSpeedL(150, 150); delay(br);

    mos(10 * sp, 10 * sp); check();
    while (sum == 0) {
      check(); if (cl < peak) cl++;
    }
    while (sum != 0) {
      check(); if(cl < peak) cl++;
    }
    braking_mechanism(1);

    (a == 1) ? motorSpeedR(150, 150) : motorSpeedL(150, 150); check();
    while (sensor[2] == 0 && sensor[3] == 0) check();
    (a == 1) ? motorSpeedL(150, 150) : motorSpeedR(150, 150); delay(br);

    head_light(0); lfang.write(fl); rfang.write(fr);
    counter ++;
    turn = 0;
  }
}

void  checkpost() {
  if (mi2 - mi4 > 30) {
    sf = sonarf.ping_cm();
    mi4 = mi2;
  }
  if (sf < object_boundary && sf > 5)  {
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(red, HIGH);
    braking_mechanism(1);
    lfang.write(intl);
    rfang.write(intr);
    mos(0, 0);
    delay(500);
    while (sf < object_boundary && sf > 0) {
      sf = sonarf.ping_cm();
      delay(30);
    }
    lfang.write(fl);
    rfang.write(fr);
    digitalWrite(green, 0);
    digitalWrite(blue, 0);
    digitalWrite(red, 0);
    counter ++;
    turn = 0;
  }
}
