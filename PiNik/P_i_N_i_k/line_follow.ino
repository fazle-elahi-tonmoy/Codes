void line_follow(byte maze, byte initial) {
  display.clearDisplay();
  text("  GOOO!!  ", 04, 25);
  display.display();
  lfang.write(fl);
  rfang.write(fr);
  delay(100);
  if (maze == 1) counter = EEPROM.read(6);
  mos(100, 100);
  delay(100);

a:
  while (digitalRead(mb) == HIGH) {
    check();
    if (sum == 0) {
      if (mov != 0) {
        if (tcount == 1) {
          (side == 2) ? scan[counter] = 3 : scan[counter] = 1;
          tcount = 0;
          counter++;
          digitalWrite(blue, HIGH);
        }
        digitalWrite(green, HIGH);
        braking_mechanism(1);
        (mov == 1) ? mos(tsp, -tsp) : mos(-tsp, tsp);
        while (!s[2] && !s[3]) check();
        if (br != 0) (mov == 1) ? mos(-tsp, tsp) : mos(tsp, -tsp);
        delay(br);
        k = 0;
        mov = 0;
        mos(10 * sp, 10 * sp);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      } else if (k < 4 && k > -4) {
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis();
          check();
          if (m82 - m81 > mtd) {
            if (maze != 0) {
              scan[counter] = 4;
              counter++;
              digitalWrite(blue, HIGH);
            }
            braking_mechanism(1);
            digitalWrite(red, HIGH);
            digitalWrite(green, HIGH);
            (side == 2) ? mos(-tsp, tsp) : mos(tsp, -tsp);
            while (s[3] == 0 && s[2] == 0) check();
            if (br != 0) (side == 2) ? mos(tsp, -tsp) : mos(-tsp, tsp);
            delay(br);
            digitalWrite(red, LOW);
            digitalWrite(green, LOW);
            digitalWrite(blue, LOW);
            (side == 2) ? k = -5 : k = 5;
          }
        }
      }
    }  //.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      if (cross != 0) {
        digitalWrite(blue, HIGH);
        braking_mechanism(1);
        (cross == 1) ? mos(tsp, -tsp) : mos(-tsp, tsp);
        while (s[1] + s[2] + s[3] + s[4]) check();
        while (!s[3] && !s[2]) check();
        if (br != 0) (cross == 1) ? mos(-tsp, tsp) : mos(tsp, -tsp);
        delay(br);
        k = 0;
        cross = 0;
        mos(10 * sp, 10 * sp);
        while (sum > 2) check();
        digitalWrite(blue, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 1) {
          mos(-10 * sp, 10 * sp);
          delay(k * line_d);
        } else if (k < -1) {
          mos(10 * sp, -10 * sp);
          delay(-k * line_d);
        }
        k = 0;
        mos(10 * sp, 10 * sp);
        if (cl < peak) cl++;
      }

      else if (bin == 4) {
        mos(10 * sp, 9 * sp);
        if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(9 * sp, 10 * sp);
        if (cl < peak) cl++;
      }
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
        if (cl > base) cl--;
      }

      else if (bin == 1) {
        if (k < 5) {
          mos(10 * sp, -10 * sp);
          delay(dt);
          k = 5;
        }
        mos(10 * sp, (9 - 4 * line_p) * sp);
        if (cl > base) cl--;
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
        if (cl > base) cl--;
      }

      else if (bin == 32) {
        if (k > -5) {
          mos(-10 * sp, 10 * sp);
          delay(dt);
          k = -5;
        }
        mos((9 - 4 * line_p) * sp, 10 * sp);
        if (cl > base) cl--;
      }
    }  //...........................................................................end sum 1

    //..............................................................................sum3
    else if (sum == 3 || sum == 4 || sum == 5) {
      //      mos(50, 50);
      if (s[0] && !s[5] && s[2] + s[3] > 0) {
        mov = 1;
        if (side == 1 || maze != 0) {
          while (s[0] && !s[5]) check();
          if (!s[5]) {
            m81 = millis();
            while (sum != 0) {
              check();
              if (millis() - m81 >= ltd) {
                if (side == 1) cross = 1;
                if (maze != 0) {
                  (side == 1) ? scan[counter] = 1 : scan[counter] = 2;
                  counter++;
                  digitalWrite(blue, HIGH);
                }
                break;
              }
            }
          }
        }
      }

      else if (!s[0] && s[5] && s[2] + s[3] > 0) {
        mov = 2;
        if (side == 2 || maze != 0) {
          while (!s[0] && s[5]) check();
          if (!s[0]) {
            m81 = millis();
            while (sum != 0) {
              check();
              if (millis() - m81 >= ltd) {
                if (side == 2) cross = 2;
                if (maze != 0) {
                  (side == 2) ? scan[counter] = 3 : scan[counter] = 2;
                  counter++;
                  digitalWrite(blue, HIGH);
                }
                break;
              }
            }
          }
        }
      }
      mi1 = millis();
    }  // ...................................................................end of sum=3,4,5

    //...........................................................................sum=6
    else if (sum == 6) {
      //      mos(50, 50);
      digitalWrite(red, HIGH);
      (side == 1) ? mov = 1 : mov = 2;
      if (maze == 1) tcount = 1;
      m81 = millis();
      while (s[0] == 1 || s[5] == 1) {
        check();
        if (millis() - m81 >= stp_delay) {
          if (sum == 6) {
            braking_mechanism(1);
            mos(0, 0);
            if (maze != 0) {
              display.clearDisplay();
              text("   DONE   ", 04, 26);
              display.display();
              scan[counter] = 0;
              algorithm();
              if (initial == 1) {
                digitalWrite(red, LOW);
                line_solve(1, 1);
                return;
              }
            }
            while (sum == 6 && digitalRead(mb) == HIGH) check();
          }
          digitalWrite(red, LOW);
          goto a;
        }
      }
      m81 = millis();
      while (sum != 0) {
        check();
        if (millis() - m81 >= ltd) {
          if (side == 1) cross = 1;
          else if (side == 2) cross = 2;
          if (maze != 0) {
            (side == 2) ? scan[counter] = 3 : scan[counter] = 1;
            counter++;
            digitalWrite(blue, HIGH);
          }
          break;
        }
      }
      digitalWrite(red, LOW);
      mi1 = millis();
    }

    if (millis() - mi1 >= 200) {
      mov = 0;
      tcount = 0;
      digitalWrite(blue, LOW);
    }
  }  //end of while loop!!!!!

  mos(0, 0);
  digitalWrite(red, LOW);
  cross = 0;
  while (digitalRead(mb) == LOW)
    ;
  lfang.write(intl);
  rfang.write(intr);
}  //line following function
