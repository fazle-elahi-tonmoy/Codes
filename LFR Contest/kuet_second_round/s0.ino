if (sum == 0) {

  sonar();

  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(100);

      while (bin != 3) {
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
      delay(100);

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
      delay(100);

      while (bin != 48) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(7 * dt);
      k30 = 0;
      mov = 0;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      delay(100);

      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(4 * dt);
      k90 = 0;
      mov = 0;

      digitalWrite(d90, LOW);
    }

  }

  else if (mov == 0) {
    if (sf <= 15 && sf != 0) wall_obstacle();
//    if (sl <= 15 && sl != 0) wall_cave();
  }



}//end of sum 0

