if (sum == 0) {


  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(10*dt);

      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(7 * dt);
      k30 = 0;
      mov = 0;
      digitalWrite(d30, LOW);
    }

    else if (k90 == 1) {
      digitalWrite(d90, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(10*dt);

      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);

      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(4 * dt);
      k90 = 0;
      mov = 0;

      digitalWrite(d90, LOW);
    }

  }


  else if (mov == 2) {

    if (k30 == 2) {
      digitalWrite(d30, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(10*dt);

      while (bin != 12) {
        check();
        motorSpeedL(8 * spr, 8 * spl);
      }
      motorSpeedR(8 * spr, 8 * spl);
      delay(7 * dt);
      k30 = 0;
      mov = 0;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(10*dt);

      while (bin != 12) {
        check();
        motorSpeedL(8 * spr, 8 * spl);
      }
      motorSpeedR(8 * spr, 8 * spl);
      delay(4 * dt);
      k90 = 0;
      mov = 0;

      digitalWrite(d90, LOW);
    }

  }







}//end of sum 0

