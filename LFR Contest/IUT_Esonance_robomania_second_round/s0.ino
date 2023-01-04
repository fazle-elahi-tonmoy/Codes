if (sum == 0) {

  if (mov == 1 ) {
    if (k30 == 1) {
      digitalWrite(d30, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      brake = cl / d;
      delay(brake);
      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);
      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(br);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }

    else if (k90 == 1) {
      digitalWrite(d90, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      brake = cl / d;
      delay(brake);
      while (bin != 12) {
        check();
        motorSpeedR(6 * spr, 6 * spl);

      }
      motorSpeedL(6 * spr, 6 * spl);
      delay(br);
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
      motorSpeedB(10 * spr, 10 * spl);
      brake = cl / d;
      delay(brake);
      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(br);
      k30 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d30, LOW);
    }
    else if (k90 == 2) {
      digitalWrite(d90, HIGH);
      motorSpeedB(10 * spr, 10 * spl);
      brake = cl / d;
      delay(brake);
      while (bin != 12) {
        check();
        motorSpeedL(6 * spr, 6 * spl);
      }
      motorSpeedR(6 * spr, 6 * spl);
      delay(br);
      k90 = 0;
      mov = 0;
      cl = base;
      brake = cl / d;
      k = 0;
      digitalWrite(d90, LOW);
    }

  }

//  else if (sl <= 12 && sl != 0) {
//    sl = 0;
//    for (int i = 1; i <= 50; i++) {
//      s[i] = sonarl.ping_cm();
//      sl = sl + s[i];
//    }
//    sl = sl / 50;
//    if (sl > 5 && sl <= 12) wall_cave();
//  }

 else  if (sl > 5 && sl <= 12) wall_cave();




}//end of sum 0
