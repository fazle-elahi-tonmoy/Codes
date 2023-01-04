if (sum == 0) {


  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(200, 200);;
      delay(brake);
      motorSpeedS();
      delay(200);

      while (sensor[0] == 0) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(5 * dt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }

    else if (k90 == 1) {
      digitalWrite(d90, HIGH);
      motorSpeedB(200, 200);;
      delay(brake);
      motorSpeedS();
      delay(200);

      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);

      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(5 * dt);
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
      motorSpeedB(200, 200);;
      delay(brake);
      motorSpeedS();
      delay(200);

      while (sensor[5] == 0) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(5 * dt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(200, 200);;
      delay(brake);
      motorSpeedS();
      delay(200);

      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(5 * dt);
      k90 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d90, LOW);
    }

  }

  else if (mov == 0 && counter == 0) {
    delay(200);
    digitalWrite(d90, HIGH);
    motorSpeedB(250, 250);
    delay(brake);

    if (side == 2) {
      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(5 * dt);
    }

    else if (side == 1) {
      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(5 * dt);
    }
    cl = base;
    brake = cl / d;
    digitalWrite(d90, LOW);
  }







}//end of sum 0
