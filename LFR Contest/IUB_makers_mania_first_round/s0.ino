if (sum == 0) {


  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(200, 200);
      delay(brake);
      motorSpeedS();
      delay(150);

      while (sensor[0] == 0) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(bt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }

    else if (k90 == 1) {
      digitalWrite(d90, HIGH);
      motorSpeedB(200, 200);
      delay(brake);
      motorSpeedS();
      delay(150);

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
      k = 0;
      digitalWrite(d90, LOW);
    }

  }


  else if (mov == 2) {

    if (k30 == 2) {
      digitalWrite(d30, HIGH);
      motorSpeedB(200, 200);
      delay(brake);
      motorSpeedS();
      delay(150);

      while (sensor[5] == 0) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(bt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(200, 200);
      delay(brake);
      motorSpeedS();
      delay(150);

      while (bin != 12) {
        check();

        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(bt);
      k90 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d90, LOW);
    }

  }

  else if (mov == 0 && counter1 >= 1) {
    delay(200);
    digitalWrite(d90, HIGH);
    motorSpeedB(250, 250);
    delay(brake);

    while (bin != 12) {
      check();
      motorSpeedL(6 * spr, 6 * spl);
    }
    motorSpeedR(6 * spr, 6 * spl);
    delay(bt);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    k = 0;
    digitalWrite(d90, LOW);
  }







}//end of sum 0
