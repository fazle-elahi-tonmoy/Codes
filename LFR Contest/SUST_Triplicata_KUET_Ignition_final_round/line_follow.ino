void line_follow() {
  delay(200);
  while (digitalRead(mb) == HIGH) {
    check();
    if (sum == 0) {
      if (mov == 1 ) {
        if (k30 != 0) {
          digitalWrite(blue, HIGH);
          braking_mechanism(1);
          motorSpeedR(8 * spl, 8 * spr);
          while (sensor[1] == 0 && sensor[4] == 0) check();
        }
        else if (k90 != 0) {
          digitalWrite(green, HIGH);
          braking_mechanism(1);
          motorSpeedR(8 * spl, 8 * spr);
          while (sensor[1] == 0 && sensor[4] == 0) check();
        }
        motorSpeedL(8 * spl, 8 * spr);
        delay(br);
        mos(5 * spl, 5 * spr);
        if (tcount == 1) {
          tcount = 0;
          counter ++;
        }
      }
      else if (mov == 2) {
        if (k30 != 0) {
          digitalWrite(blue, HIGH);
          braking_mechanism(1);
          motorSpeedL(8 * spl, 8 * spr);
          while (sensor[1] == 0 && sensor[4] == 0) check();
        }
        else if (k90 != 0) {
          braking_mechanism(1);
          digitalWrite(green, HIGH);
          motorSpeedL(8 * spl, 8 * spr);
          while (sensor[1] == 0 && sensor[4] == 0) check();
        }
        motorSpeedR(8 * spl, 8 * spr);
        delay(br);
        mos(5 * spl, 5 * spr);
        if (tcount == 1) {
          tcount = 0;
          counter ++;
        }
      }
//      else if (wall_trigger(2) == 1) wall_follow();
      else if (mov == 0) {
        if (k == 0) mos(10 * spl, 10 * spr);
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis();
          check();
          if (m82 - m81 > mtd) {
            if (counter != 2) {
              counter = 5;
              break;
            }
            digitalWrite(7, HIGH);
            braking_mechanism(1.5);
            motorSpeedR(8 * spl, 8 * spr);
            while (sensor[1] == 0 && sensor[4] == 0) check();
            motorSpeedL(8 * spl, 8 * spr);
            delay(br);
            if (counter == 2) counter = 3;
            digitalWrite(7, LOW);
            break;
          }
        }
      }

      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      if (cross == 1) {
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
        braking_mechanism(1);
        motorSpeedR(8 * spl, 8 * spr);
        check();
        while (sensor[1] == 1) check();
        while (sensor[1] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedL(8 * spl, 8 * spr);
        delay(br);
        mos(5 * spl, 5 * spr);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      else if (cross == 2) {
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
        braking_mechanism(1);
        motorSpeedL(8 * spl, 8 * spr);
        check();
        while (sensor[5] == 1) check();
        while (sensor[5] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedR(8 * spl, 8 * spr);
        delay(br);
        mos(5 * spl, 5 * spr);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 0) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
        }
        else if (k < 0) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
        }
        k = 0;
        mos(10 * spl, 10 * spr);
        if (cl < peak) cl++;
      }
      else if (bin == 4) {
        mos(10 * spl, 9 * spr);
        if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(9 * spl, 10 * spr);
        if (cl < peak) cl++;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 2;
        }
        mos(10 * spl, 7 * spr);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 3;
        }
        mos(10 * spl, 4 * spr);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 4;
        }
        mos( 10 * spl, 0 * spr);
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 5;
        }
        mos(10 * spl, -3 * spr);
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -2;
        }
        mos(7 * spl, 10 * spr);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -3;
        }
        mos(4 * spl, 10 * spr);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -4;
        }
        mos(0 * spl, 10 * spr);
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -5;
        }
        mos(-3 * spl, 10 * spr);
      }
    }//...........................................................................end sum 1

    //..............................................................................sum3
    else if (sum == 3 || sum == 4 || sum == 5) {
      if (bin == 11 || bin == 13 || bin == 25 || bin == 19) {
        k30 = 1;
        mov = 1;
      }

      else if ( bin == 52 || bin == 44 || bin == 38 || bin == 50) {
        k30 = 2;
        mov = 2;
      }

      else if (bin == 7 || bin == 15 || bin == 31) {
        k90 = 1;
        mov = 1;
        if (counter == 3) {
          m81 = m82 = millis();
          while (sum != 6 && sum != 0) {
            check();
            m82 = millis();
            if (m82 - m81 >= 50) {
              cross = 1;
              counter = 4;
              break;
            }
          }
        }
      }

      else if (bin == 56 || bin == 60 || bin == 62) {
        mov = 2;
        k90 = 2;
      }
      mi1 = millis();
    }// ...................................................................end of sum=3,4,5

    //...........................................................................sum=6
    else if (sum == 6) {
      digitalWrite(red, HIGH);
      mov = 1;
      k90 = 1;
      m81 = m82 = millis();
      while (sum != 0) {
        check();
        m82 = millis();
        if (m82 - m81 >= 50) {
          if (sum == 6) {
            braking_mechanism(1);
            mos(0, 0);
            int i = 0;
            while (sum == 6) {
              check();
              i++;
              delay(1);
              if (digitalRead(mb) == LOW) break;
            }
            if (digitalRead(mb) == HIGH && i > 200) delay(500);
            break;
          }
          else {
            mov = 0;
            if (counter == 0 || counter == 1) {
              counter ++;
              cross = 1;
            }
            if (counter == 5) {
              counter = 6;
              head_light(1);
              spl = 23;
              spr = 23;
            }
            break;
          }
        }
      }
      digitalWrite(red, LOW);
      mi1 = millis();
    }

    mi2 = millis();
    if (mi2 - mi1 >= 200)  mov = 0; //500ms por movement automatic 0 korar command

  }//end of while loop!!!!!4
  mos(0, 0);
  while (digitalRead(mb) == LOW);
}//line following function
