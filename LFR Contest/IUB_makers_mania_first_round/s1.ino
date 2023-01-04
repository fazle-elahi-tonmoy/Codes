else if (sum == 1 || sum == 2) {

  if (cross == 1) {
    cross = 0;
    digitalWrite(d90, HIGH);
    motorSpeedB(200, 200);
    delay(brake * 2);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedR(6 * spr, 6 * spl);

    }
    while (sensor[3] == 0) {
      check();
      motorSpeedR(6 * spr, 6 * spl);

    }
    motorSpeedL(6 * spr, 6 * spl);
    delay(bt);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    digitalWrite(d90, LOW);
    digitalWrite(13, LOW);

  }
  if (cross == 2) {
    cross = 0;
    digitalWrite(d90, HIGH);
    motorSpeedB(200, 200);
    delay(brake * 2);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedL(6 * spr, 6 * spl);

    }
    while (sensor[2] == 0) {
      check();
      motorSpeedL(6 * spr, 6 * spl);

    }
    motorSpeedR(6 * spr, 6 * spl);
    delay(bt);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    digitalWrite(d90, LOW);
    digitalWrite(13, LOW);

  }


  else if (bin == 12) {
    if (k > 0) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
    }
    else if (k < 0) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
    }
    k = 0;
    mos(10 * spr, 10 * spl);
    cl++;
    if (cl > peak) cl = peak;
    brake = cl / d;
  }
  else if (bin == 4) {
    mos(9 * spr, 10 * spl);
    cl++;
    if (cl > peak) cl = peak;
    brake = cl / d;
  }
  else if (bin == 8) {
    mos(10 * spr, 9 * spl);
    cl++;
    if (cl > peak) cl = peak;
    brake = cl / d;
  }

  else if (bin == 6) {
    if (k < 2) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 2;
    }
    mos(7 * spr, 10 * spl);
  }

  else if (bin == 2) {
    if (k < 3) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 3;
    }
    mos(4 * spr, 10 * spl);
  }

  else if (bin == 3) {
    if (k < 4) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 4;
    }
    mos(-5 * spr, 10 * spl);
  }
  else if (bin == 1) {
    if (counter1 >= 1) {
      motorSpeedB(200, 200);
      delay(brake*2);
      motorSpeedS();
      delay(150);
      cl = base;
      brake = cl / d;
    }
    if (k < 5) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 5;
    }
    mos(-7 * spr, 10 * spl);
    mov = 1;
  }

  // dan side shesh


  // bam side shuru

  else if (bin == 24) {
    if (k > -2) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -2;
    }
    mos(10 * spr, 7 * spl);
  }
  else if (bin == 16) {
    if (k > -3) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -3;
    }
    mos(10 * spr, 4 * spl);
  }

  else if (bin == 48) {
    if (k > -4) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -4;
    }
    mos(10 * spr, -5 * spl);
  }
  else if (bin == 32) {
    if (counter1 >= 1) {
      motorSpeedB(200, 200);
      delay(brake*2);
      motorSpeedS();
      delay(150);
      cl = base;
      brake = cl / d;
    }
    if (k > -5) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -5;
    }
    mos(10 * spr, -7 * spl);
    mov = 1;

  }




}//end sum 1
