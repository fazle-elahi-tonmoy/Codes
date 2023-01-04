void wall_follow() {
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    if (counter == 0) {
      if (sf > 2 && sf <= 5) {
        motorSpeedB(spr * 8, spl * 8);
        delay(50);
        motorSpeedS();
        handle.write(0);
        delay(500);
        grab.write(140);
        delay(500);
        hpos = EEPROM.read(8);
        handle.write(hpos);
        while (sr <= 5 || sr >= 15) {
          sonar();
          motorSpeedR(150, 150);
        }
        motorSpeedL(150, 150);
        delay(40);
        motorSpeedS();
        counter = 1;
      }
      else if (sl <= 8 && sl > 0) mos(0, 150);
      else if (sl >= 12 && sl <= 20) mos(150, 0);
      else mos(spr * 8, spl * 8);
    }

    if (counter == 1) {
      if (sf > 2 && sf <= 10) {
        motorSpeedB(spr * 8, spl * 8);
        delay(50);
        motorSpeedS();
        motorSpeedL(200, 200);
        delay(450);
        motorSpeedR(200, 200);
        delay(40);
        motorSpeedS();
        counter = 2;
      }
      else if (sr <= 8 && sr > 0) mos(150, 0);
      else if (sr >= 12 && sr <= 20) mos(0, 150);
      else mos(spr * 8, spl * 8);
    }
    if (counter == 2) {
      sonar();
      if (sf > 2 && sf <= 18) {
        motorSpeedB(spr * 8, spl * 8);
        delay(50);
        motorSpeedS();
        hpos = EEPROM.read(8);
        gpos = EEPROM.read(9);
        grab.write(140);
        delay(500);
        handle.write(0);
        delay(500);
        grab.write(gpos);
        delay(500);
        handle.write(hpos);
        delay(1000);
        motorSpeedL(200, 200);
        delay(d_counter);
        motorSpeedR(200, 200);
        delay(40);
        motorSpeedS();
        counter = 3;
      }
      else if (sr <= 8 && sr > 0) mos(150, 0);
      else if (sr >= 12 && sr <= 20) mos(0, 150);
      else mos(spr * 8, spl * 8);
    }
    if (counter == 3) {
      sonar();
      while (sf <= 2 || sf >= 10) {
        sonar();
        mos(spr * 8, spl * 8);
      }
      motorSpeedB(spr * 8, spl * 8);
      delay(50);
      motorSpeedS();
      handle.write(0);
      delay(500);
      grab.write(140);
      delay(500);
      hpos = EEPROM.read(8);
      handle.write(hpos);
      motorSpeedB(8*spr, 8*spl);
      delay(500);
      motorSpeedS();
      counter=4;
    }

  }
}

