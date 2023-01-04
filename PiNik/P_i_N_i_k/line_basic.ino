void basic_line_follow() {
  display.clearDisplay();
  text("  GOOO!!  ", 04, 25);
  display.display();
  lfang.write(fl);
  rfang.write(fr);
  delay(100);
  mos(100, 100);
  delay(100);
  while (digitalRead(mb) == HIGH) {
    check();
    if (bin == 12) {
      if (k > 1) {
        mos(-10 * sp, 10 * sp);
        delay(k * line_d);
      } else if (k < -1) {
        mos(10 * sp, -10 * sp);
        delay(-k * line_d);
      }
      k = 0;
      mos(10 * sp, 10 * sp);
    }

    else if (bin == 4) mos(10 * sp, 9 * sp);
    else if (bin == 8) mos(9 * sp, 10 * sp);
    //..................................................left side position
    else if (bin == 6) {
      if (k < 2) {
        mos(10 * sp, -10 * sp);
        delay(dt);
        k = 2;
      }
      mos(10 * sp, (9 - line_p) * sp);
    }

    else if (bin == 2) {
      if (k < 3) {
        mos(10 * sp, -10 * sp);
        delay(dt);
        k = 3;
      }
      mos(10 * sp, (9 - 2 * line_p) * sp);
    }

    else if (bin == 3) {
      if (k < 4) {
        mos(10 * sp, -10 * sp);
        delay(dt);
        k = 4;
      }
      mos(10 * sp, (9 - 3 * line_p) * sp);
    }

    else if (bin == 1) {
      if (k < 5) {
        mos(10 * sp, -10 * sp);
        delay(dt);
        k = 5;
      }
      mos(10 * sp, (9 - 4 * line_p) * sp);
    }
    // ..................................................dan side shesh
    // .....................................................bam side shuru
    else if (bin == 24) {
      if (k > -2) {
        mos(-10 * sp, 10 * sp);
        delay(dt);
        k = -2;
      }
      mos((9 - line_p) * sp, 10 * sp);
    }

    else if (bin == 16) {
      if (k > -3) {
        mos(-10 * sp, 10 * sp);
        delay(dt);
        k = -3;
      }
      mos((9 - 2 * line_p) * sp, 10 * sp);
    }

    else if (bin == 48) {
      if (k > -4) {
        mos(-10 * sp, 10 * sp);
        delay(dt);
        k = -4;
      }
      mos((9 - 3 * line_p) * sp, 10 * sp);
    }

    else if (bin == 32) {
      if (k > -5) {
        mos(-10 * sp, 10 * sp);
        delay(dt);
        k = -5;
      }
      mos((9 - 4 * line_p) * sp, 10 * sp);
    } 
    
    else if (s[5] && s[0]) mos(10 * sp, 10 * sp);
    else if (s[5]) mos((9 - 4 * line_p) * sp, 10 * sp);
    else if (s[0]) mos(10 * sp, (9 - 4 * line_p) * sp);


  }  //end of while loop!!!!!

  mos(0, 0);
  digitalWrite(red, LOW);
  cross = 0;
  while (digitalRead(mb) == LOW)
    ;
  lfang.write(intl);
  rfang.write(intr);
}  //line following function
