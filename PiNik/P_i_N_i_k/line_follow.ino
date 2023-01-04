void line_follow(byte maze, byte initial) {
  display.clearDisplay(); text("  GOOO!!  ", 04, 25); display.display();
  lfang.write(fl); rfang.write(fr); delay(100);
  if (maze == 1) counter = EEPROM.read(6);
  mos(100, 100); delay(100);

a:  while (digitalRead(mb) == HIGH) {
    check();
    if (maze == 0) inverse_y();
    if (sum == 0) {
      if (mov == 1 ) {
        if (k30 != 0) digitalWrite(blue, HIGH);
        else if (k90 != 0) digitalWrite(green, HIGH);
        braking_mechanism(1); motorSpeedR(tsp, tsp);
        while (sum == 0) check();
        if (br != 0) motorSpeedL(tsp, tsp); delay(br);
        mos(100, 100); k = 5;
        if (tcount == 1) {
          scan[counter] = 1; tcount = 0; counter++;
        }
      }
      else if (mov == 2) {
        if (k30 != 0) digitalWrite(blue, HIGH);
        else if (k90 != 0) digitalWrite(green, HIGH);
        braking_mechanism(1); motorSpeedL(tsp, tsp);
        while (sum == 0) check();
        if (br != 0) motorSpeedR(tsp, tsp); delay(br);
        k = -5; mos(100, 100);
        if (tcount == 1) {
          scan[counter] = 3; tcount = 0; counter++;
        }
      }
      else if (mov == 0 && k < 4 && k > -4) {
        mos(70, 70);
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis(); check();
          if (m82 - m81 > mtd) {
            braking_mechanism(1);
            digitalWrite(red, HIGH); digitalWrite(green, HIGH);
            (side == 2) ?  motorSpeedL(tsp, tsp) : motorSpeedR(tsp, tsp);
            while (sensor[4] == 0 && sensor[3] == 0 && sensor[2] == 0 && sensor[1] == 0) check();
            if (br != 0) (side == 2) ? motorSpeedR(tsp, tsp) : motorSpeedL(tsp, tsp);
            delay(br);
            if (maze != 0) {
              scan[counter] = 4; counter++;
            }
            digitalWrite(red, LOW); digitalWrite(green, LOW);
            (side == 2) ? k = -5 : k = 5;
          }
        }
      }
      digitalWrite(green, LOW); digitalWrite(blue, LOW);
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      if (cross == 1) {
        digitalWrite(green, HIGH); digitalWrite(blue, HIGH);
        braking_mechanism(1); motorSpeedR(tsp, tsp);
        while (sensor[1] == 1 || sensor[2] == 1 || sensor [3] == 1 || sensor[4] == 1) check();
        while (sensor[4] == 0 && sensor[3] == 0 && sensor[2] == 0 && sensor[1] == 0) check();
        if (br != 0) motorSpeedL(tsp, tsp); delay(br);
        k = 5; mos(100, 100);
        digitalWrite(green, LOW); digitalWrite(blue, LOW);
      }
      else if (cross == 2) {
        digitalWrite(green, HIGH); digitalWrite(blue, HIGH);
        braking_mechanism(1); motorSpeedL(tsp, tsp);
        while (sensor[1] == 1 || sensor[2] == 1 || sensor [3] == 1 || sensor[4] == 1) check();
        while (sensor[4] == 0 && sensor[3] == 0 && sensor[2] == 0 && sensor[1] == 0) check();
        if (br != 0) motorSpeedR(tsp, tsp); delay(br);
        k = -5; mos(100, 100);
        digitalWrite(green, LOW); digitalWrite(blue, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 1) {
          motorSpeedL(10 * sp, 10 * sp); delay(k * line_d);
        }
        else if (k < -1) {
          motorSpeedR(10 * sp, 10 * sp); delay(-k * line_d);
        }
        k = 0; mos(10 * sp, 10 * sp);
        if (cl < peak) cl++;
      }
      else if (bin == 4) {
        mos(10 * sp, 9 * sp); if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(9 * sp, 10 * sp); if (cl < peak) cl++;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * sp, 10 * sp); delay(dt); k = 2;
        }
        mos(10 * sp, (9 - line_p) * sp);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * sp, 10 * sp); delay(dt); k = 3;
        }
        mos(10 * sp, (9 - 2 * line_p) * sp);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * sp, 10 * sp); delay(dt); k = 4;
        }
        mos( 10 * sp, (9 - 3 * line_p) * sp);
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * sp, 10 * sp); delay(dt); k = 5;
        }
        mos(10 * sp, (9 - 4 * line_p) * sp);
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * sp, 10 * sp); delay(dt); k = -2;
        }
        mos((9 - line_p)* sp, 10 * sp);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * sp, 10 * sp); delay(dt); k = -3;
        }
        mos((9 - 2 * line_p) * sp, 10 * sp);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * sp, 10 * sp); delay(dt); k = -4;
        }
        mos((9 - 3 * line_p) * sp, 10 * sp);
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * sp, 10 * sp); delay(dt); k = -5;
        }
        mos((9 - 4 * line_p) * sp, 10 * sp);
      }
    }//...........................................................................end sum 1

    //..............................................................................sum3
    else if (sum == 3 || sum == 4 || sum == 5) {
      mos(50, 50);
      if (maze == 0 && sensor[0] == 1 && sensor [1] == 0 && (sensor [2] == 1 || sensor [3] == 1) ) {
        k30 = 1; mov = 1;
      }

      else if (maze == 0 && sensor [5] == 1 && sensor [4] == 0 && (sensor [2] == 1 || sensor [3] == 1)) {
        k30 = 2; mov = 2;
      }

      else if (bin == 7 || bin == 15 || bin == 31) { //31 mane 011111
        k90 = 1; mov = 1;
        if (side == 1 || maze != 0) {
          while (sensor[0] == 1 && sensor[5] == 0) check();
          if (sensor[5] == 0) {
            m81 = m82 = millis();
            while (sum != 0) {
              check(); m82 = millis();
              if (m82 - m81 >= ltd) {
                if (side == 1) cross = 1;
                if (maze != 0) {
                  (side == 1) ? scan[counter] = 1 : scan[counter] = 2; counter++;
                }
                break;
              }
            }
          }
        }
      }
      else if (bin == 56 || bin == 60 || bin == 62) {   //62 mane 111110
        k90 = 2; mov = 2;
        if (side == 2 || maze != 0) {
          while (sensor[0] == 0 && sensor[5] == 1) check();
          if (sensor[0] == 0) {
            m81 = m82 = millis();
            while (sum != 0) {
              check(); m82 = millis();
              if (m82 - m81 >= ltd) {
                if (side == 2) cross = 2;
                if (maze != 0) {
                  (side == 2) ? scan[counter] = 3 : scan[counter] = 2;  counter++;
                }
                break;
              }
            }
          }
        }
      }
      mi1 = millis();
    }// ...................................................................end of sum=3,4,5

    //...........................................................................sum=6
    else if (sum == 6) {
      mos(50, 50); k30 = 0; digitalWrite(red, HIGH);
      (side == 1) ? mov = 1 : mov = 2;
      (side == 1) ? k90 = 1 : k90 = 2;
      if (maze == 1) tcount = 1;
      m81 = m82 = millis();
      while (sensor[0] == 1 || sensor [5] == 1) {
        check(); m82 = millis();
        if (m82 - m81 >= stp_delay) {
          if (sum == 6) {
            braking_mechanism(1); mos(0, 0);
            if (maze != 0) {
              display.clearDisplay(); text("   DONE   ", 04, 26); display.display();
              scan[counter] = 0; algorithm();
              if (initial == 1) {
                digitalWrite(red, LOW); line_solve(1, 1); return;
              }
            }
            while (sum == 6 && digitalRead(mb) == HIGH) check();
          }
          digitalWrite(red, LOW); goto a ;
        }
      }
      m81 = m82 = millis();
      while (sum != 0) {
        check(); m82 = millis();
        if (m82 - m81 >= ltd) {
          if (side == 1) cross = 1;
          else if (side == 2) cross = 2;
          if (maze != 0) {
            (side == 2) ? scan[counter] = 3 : scan[counter] = 1; counter++;
          }
          break;
        }
      }
      digitalWrite(red, LOW); mi1 = millis();
    }

    mi2 = millis();
    if (mi2 - mi1 >= 200) {
      mov = 0;
      tcount = 0;
    }
  }//end of while loop!!!!!

  mos(0, 0); digitalWrite(red, LOW); cross = 0;
  while (digitalRead(mb) == LOW);
  lfang.write(intl); rfang.write(intr);
}//line following function
