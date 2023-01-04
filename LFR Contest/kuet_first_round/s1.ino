else if (sum == 1 || sum == 2) {

  if (cross == 1) {
    cross = 0;
    digitalWrite(d90, HIGH);
    motorSpeedB(10 * spr, 10 * spl);
    delay(10*dt);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedR(8 * spr, 8 * spl);

    }
    while (bin != 12) {
      check();
      motorSpeedR(8 * spr, 8 * spl);

    }
    motorSpeedL(8 * spr, 8 * spl);
    delay(40);
    k90 = 0;
    mov = 0;
    digitalWrite(d90, LOW);
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
  }
  else if (bin == 4) {
    mos(9 * spr, 10 * spl);
  }
  else if (bin == 8) {
    mos(10 * spr, 9 * spl);
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
    mos(4.5 * spr, 10 * spl);
  }

  else if (bin == 3) {
    if (k < 4) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 4;
    }
    mos(-3 * spr, 10 * spl);
  }
  else if (bin == 1) {
    if (k < 5) {
      motorSpeedR(10 * spr, 10 * spl);
      delay(dt);
      k = 5;
    }
    mos(-5 * spr, 10 * spl);
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
    mos(10 * spr, 4.5 * spl);
  }

  else if (bin == 48) {
    if (k > -4) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -4;
    }
    mos(10 * spr, -3 * spl);
  }
  else if (bin == 32) {
    if (k > -5) {
      motorSpeedL(10 * spr, 10 * spl);
      delay(dt);
      k = -5;
    }
    mos(10 * spr, -5 * spl);
  }

//  else if (bin == 5 || bin == 9) {
//    mov=1;
//    k30=1;
//  }
//  else if (bin == 36 || bin == 40){
//    mov=2;
//    k30=2;
//  }


}//end sum 1

