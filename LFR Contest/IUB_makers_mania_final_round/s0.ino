if (sum == 0) {


  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(250, 250);
      delay(brake);

      while (bin != 3) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(7 * dt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      digitalWrite(d30, LOW);
    }

    else if (k90 == 1) {
      digitalWrite(d90, HIGH);
      motorSpeedB(250, 250);
      delay(brake);

      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);

      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(4 * dt);
      k90 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      digitalWrite(d90, LOW);
    }

  }


  else if (mov == 2) {

    if (k30 == 2) {
      digitalWrite(d30, HIGH);
      motorSpeedB(250, 250);
      delay(brake);

      while (bin != 48) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(7 * dt);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(250, 250);
      delay(brake);

      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(4 * dt);
      k90 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      digitalWrite(d90, LOW);
    }

  }

  else if (mov == 0) {
    if (counter == 0) counter = 1;
    if (tcount == 1) {
      if (counter == 1) {
        digitalWrite(calout, HIGH);
        while (sum != 6 && sum != 5) {
          check();
          mos(10 * spr, 10 * spl);
        }
        while (sum != 2) {
          check();
          mos(10 * spr, 10 * spl);
        }
        counter = 2;
        tcount = 0;
        digitalWrite(calout, LOW);
      }

      else if (counter == 3) {
        digitalWrite(d30, HIGH);
        motorSpeedB(250, 250);
        delay(brake);
                while (bin != 12) {
                  check();
                  motorSpeedL(6 * spr, 6 * spl);
                }
                motorSpeedR(6 * spr, 6 * spl);
                delay(7 * dt);
                k30 = 0;
                mov = 0;
                cl = base;
                brake = cl / d;
        counter = 4;
        digitalWrite(d30, LOW);
      }
    }



  }







}//end of sum 0
