void line_follow() {
  delay(200);
  while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) {
    check();
    if (sum == 0) {
      if (mov == 1 ) {
        if (k30 != 0) {
          digitalWrite(d30, HIGH);
          braking_mechanism(1.5);
          motorSpeedR(5 * spl, 5 * spr);
          while (sensor [0] == 0) check();
        }
        else if (k90 != 0) {
          digitalWrite(d90, HIGH);
          braking_mechanism(1);
          motorSpeedR(5 * spl, 5 * spr);
          while (sensor[2] == 0 && sensor[3] == 0) check();
        }
        motorSpeedL(5 * spl, 5 * spr);
        delay(br);
        digitalWrite(d30, LOW);
        digitalWrite(d90, LOW);
        mos(5 * spl, 5 * spr);
        if (tcount == 1) {
          tcount = 0;
          counter ++;
        }
      }
      else if (mov == 2) {
        if (k30 != 0) {
          digitalWrite(d30, HIGH);
          braking_mechanism(1.5);
          motorSpeedL(5 * spl, 5 * spr);
          while (sensor [5] == 0) check();
        }
        else if (k90 != 0) {
          digitalWrite(d90, HIGH);
          braking_mechanism(1);
          motorSpeedL(5 * spl, 5 * spr);
          while (sensor[2] == 0 && sensor[3] == 0) check();
        }
        motorSpeedR(5 * spl, 5 * spr);
        delay(br);
        digitalWrite(d30, LOW);
        digitalWrite(d90, LOW);
        mos(5 * spl, 5 * spr);
        if (tcount == 1) {
          tcount = 0;
          counter ++;
        }
      }
      else if (k <= 2 && k >= -2 ) {
        mos(10 * spl, 10 * spr);
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis();
          check();
          if (m82 - m81 > 50) {
            if(counter == 6 && sig == 0) break;
            braking_mechanism(1);
            while (sensor[2] == 0 && sensor[3] == 0) {
              check();
              motorSpeedL(6 * spl, 6 * spr);
            }
            motorSpeedR(6 * spl, 6 * spr);
            delay(br);
            sig = 0;
            if (counter == 0 || counter == 2) counter ++ ;
          }
        }
      }
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      check();
      if (cross == 1) {
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        braking_mechanism(1);
        motorSpeedR(6 * spl, 6 * spr);
        while (sensor[1] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedL(6 * spl, 6 * spr);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
        mos(5 * spl, 5 * spr);
      }
      else if (cross == 2) {
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        braking_mechanism(1);
        motorSpeedL(6 * spl, 6 * spr);
        while (sensor[5] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedR(6 * spl, 6 * spr);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
        mos(5 * spl, 5 * spr);
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
        mos(10 * spl, 8 * spr);
        if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(8 * spl, 10 * spr);
        if (cl < peak) cl++;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 2;
        }
        mos(10 * spl, 5 * spr);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 3;
        }
        mos(10 * spl, 3 * spr);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 4;
        }
        mos( 10 * spl, -3 * spr);
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * spl, 10 * spr);
          delay(dt);
          k = 5;
        }
        mos(10 * spl, -5 * spr);
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -2;
        }
        mos(5 * spl, 10 * spr);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -3;
        }
        mos(3 * spl, 10 * spr);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -4;
        }
        mos(-3 * spl, 10 * spr);
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * spl, 10 * spr);
          delay(dt);
          k = -5;
        }
        mos(-5 * spl, 10 * spr);
      }
    }//...........................................................................end sum 1

    //..............................................................................sum3
    else if (sum == 3 || sum == 4 || sum == 5) {
      if (bin == 11 || bin == 13 || bin == 25 || bin == 19) {
        k30 = 1;
        mov = 1;
        if (counter == 1) {
          m81 = m82 = millis();
          while (sum != 6 && sum != 0) {
            check();
            m82 = millis();
            if (m82 - m81 >= 80) {
              if (counter == 1) special_RHR1();
              else if (counter == 3) special_RHR2();
              break;
            }
          }
        }
      }

      else if ( bin == 52 || bin == 44 || bin == 38 || bin == 50) {
        k30 = 2;
        mov = 2;
        if (counter == 3) {
          m81 = m82 = millis();
          while (sum != 6 && sum != 0) {
            check();
            m82 = millis();
            if (m82 - m81 >= 80) {
              special_RHR2();
              break;
            }
          }
        }
      }

      else if (bin == 7 || bin == 15 || bin == 31) {
        k90 = 1;
        mov = 1;
        while (sum != 6 && sum != 0) {
          check();
          m82 = millis();
          if (m82 - m81 >= 50) {
            if (counter == 1) special_RHR1();
            else if (counter == 3) special_RHR2();
            else if (counter == 4 || counter == 5 || counter == 8) cross = 1;
            else if(counter == 6) sig = 1;
            break;
          }
        }
      }

      else if (bin == 56 || bin == 60 || bin == 62) {
        mov = 2;
        k90 = 2;
        m81 = m82 = millis();
        while (sum != 6 && sum != 0) {
          check();
          m82 = millis();
          if (m82 - m81 >= 50) {
            if (counter == 6 || counter == 7 || counter == 9) cross = 2;
            break;
          }
        }
      }
      mi1 = millis();
    }// ...................................................................end of sum=3,4,5

    //...........................................................................sum=6
    else if (sum == 6) {
      digitalWrite(d30, HIGH);
      digitalWrite(d90, HIGH);
      if (counter == 4 || counter == 5 || counter == 6 || counter == 7 || counter == 8) tcount = 1;
      k30 = 0;
      if (counter == 4 || counter == 5 || counter == 8) {
        mov = 1;
        k90 = 1;
      }
      else if (counter == 6 || counter == 7 || counter == 9) {
        mov = 2;
        k90 = 2;
      }
      m81 = m82 = millis();
      while (sum != 0) {
        check();
        m82 = millis();
        if (m82 - m81 >= 50) {
          if (sum == 6) {
            braking_mechanism(1);
            mos(0, 0);
            while (sum == 6) {
              check();
              if (digitalRead(rb) == LOW || digitalRead(lb) == LOW) break;
            }
            if (digitalRead(rb) == HIGH && digitalRead(lb) == HIGH) delay(500);
            break;
          }
          else {
            mov = 0;
            k90 = 0;
            break;
          }
        }
      }
      digitalWrite(d30, LOW);
      digitalWrite(d90, LOW);
      mi1 = millis();
    }

    mi2 = millis();
    if (mi2 - mi1 >= 100 || counter <=3)  mov = 0; //500ms por movement automatic 0 korar command

  }//end of while loop!!!!!
}//line following function
