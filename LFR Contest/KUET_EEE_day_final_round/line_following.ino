void line_follow() {
  while (digitalRead(calin) == LOW) {
    check();
    if (sf <= 12 && sf >= 2 && counter == 7) wall_obstacle();
    if (analogRead(7) > 900 && counter == 9) {
        digitalWrite(buzzer_positive, 1);
        mos(0, 0);
        while (1)
        digitalWrite(buzzer_positive, 0);
      }
    else if (sum == 0) {
      if (mov == 1 ) {
        delay(btd);
        if (k30 == 1) {
          digitalWrite(d30, HIGH);
          braking_mechanism();
          while (sensor[2] == 0 && sensor[3] == 0) {
            check();
            motorSpeedR(6 * spr, 6 * spl);
          }
          motorSpeedL(6 * spr, 6 * spl);
          delay(br);
          digitalWrite(d30, LOW);
        }
        else if (k90 == 1) {
          digitalWrite(d90, HIGH);
          braking_mechanism();
          while (sensor[2] == 0 && sensor[3] == 0) {
            check();
            motorSpeedR(6 * spr, 6 * spl);
          }
          motorSpeedL(6 * spr, 6 * spl);
          delay(br);
          digitalWrite(d90, LOW);
        }
      }
      else if (mov == 2) {
        delay(btd);
        if (k30 == 2) {
          digitalWrite(d30, HIGH);
          braking_mechanism();
          while (sensor[2] == 0 && sensor[3] == 0) {
            check();
            motorSpeedL(6 * spr, 6 * spl);
          }
          motorSpeedR(6 * spr, 6 * spl);
          delay(br);
          digitalWrite(d30, LOW);
        }
        else if (k90 == 2) {
          digitalWrite(d90, HIGH);
          braking_mechanism();
          while (sensor[2] == 0 && sensor[3] == 0) {
            check();
            motorSpeedL(6 * spr, 6 * spl);
          }
          motorSpeedR(6 * spr, 6 * spl);
          delay(br);
          digitalWrite(d90, LOW);
        }
      }
      sr = sonarr.ping_cm();
      if (sr < 30 && sr > 5 && counter < 7) wall_follow();
      else if(counter !=9) {
        //        mos(10 * spl, 10 * spr);
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis();
          check();
          if (m82 - m81 > mtd) {
            if (counter != 1 && counter != 3) break;
            digitalWrite(calout, HIGH);
            braking_mechanism();
            while (sensor[2] == 0 && sensor[3] == 0) {
              check();
              motorSpeedL(6 * spr, 6 * spl);
            }
            motorSpeedR(6 * spr, 6 * spl);
            delay(br);
            digitalWrite(calout, LOW);
            counter ++ ;
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
        braking_mechanism();
        while (sensor[0] == 1) {
          check();
          motorSpeedR(6 * spr, 6 * spl);
        }
        while (sensor[0] == 0) {
          check();
          motorSpeedR(6 * spr, 6 * spl);
        }
        while (bin != 12) {
          check();
          motorSpeedR(6 * spr, 6 * spl);
        }
        motorSpeedL(6 * spr, 6 * spl);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
      }
      if (cross == 2) {
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        braking_mechanism();
        while (sensor[5] == 1) {
          check();
          motorSpeedL(6 * spr, 6 * spl);
        }
        while (sensor[5] == 0) {
          check();
          motorSpeedL(6 * spr, 6 * spl);
        }
        while (bin != 12) {
          check();
          motorSpeedL(6 * spr, 6 * spl);
        }
        motorSpeedR(6 * spr, 6 * spl);
        delay(br);
        digitalWrite(d90, LOW);
        digitalWrite(d30, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 0) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
        }
        else if (k < 0) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
        }
        k = 0;
        mos(10 * spr, 10 * spl);
        if (cl < peak) cl++;
        sf = sonarf.ping_cm();
      }
      else if (bin == 4) {
        mos(9 * spr, 10 * spl);
        if (cl < peak) cl++;
        sf = sonarf.ping_cm();
      }

      else if (bin == 8) {
        mos(10 * spr, 9 * spl);
        if (cl < peak) cl++;
        sf = sonarf.ping_cm();
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 2;
        }
        mos(5 * spr, 10 * spl);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 3;
        }
        mos(3 * spr, 10 * spl);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 4;
        }
        mos( -3 * spr, 10 * spl);
        //mov = 1;
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 5;
        }
        mos(-5 * spr, 10 * spl);
        mov = 1;
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -2;
        }
        mos(10 * spr, 5 * spl);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -3;
        }
        mos(10 * spr, 3 * spl);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -4;
        }
        mos(10 * spr, -3 * spl);
        //mov = 2;
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -5;
        }
        mos(10 * spr, -5 * spl);
        mov = 2;
      }
    }//...........................................................................end sum 1


    //...............................................................................sum=3||sum=4||sum=5
    else if (sum == 3 || sum == 4 || sum == 5) {
      tcount = 0;
      if (bin == 11 || bin == 13 || bin == 9 || bin == 25 || bin == 19) {
        k30 = 1;
        mov = 1;
      }

      else if ( bin == 52 || bin == 44 || bin == 36 || bin == 38 || bin == 50) {
        k30 = 2;
        mov = 2;
        if (counter == 0 || counter == 2) {
          m81 = m82 = millis();
          while (sum != 6 && sum != 0) {
            check();
            m82 = millis();
            if (m82 - m81 >= 180) {
              if (counter == 0) special_LHR();
              else if (counter == 2) special_RHR();
              break;
            }
          }
        }
      }

      else if (bin == 7 || bin == 15 || bin == 31) { //31 mane 011111
        k90 = 1;
        mov = 1;
        m81 = m82 = millis();
        while (sum != 6 && sum != 0) {
          check();
          m82 = millis();
          if (m82 - m81 >= 120) {
            if (counter == 2) special_RHR();
            break;
          }
        }
      }
      else if (bin == 56 || bin == 60 || bin == 62) {   //62 mane 111110
        k90 = 2;
        mov = 2;
        m81 = m82 = millis();
        while (sum != 6 && sum != 0) {
          check();
          m82 = millis();
          if (m82 - m81 >= 120) {
            if (counter == 0) special_LHR();
            else if (counter == 2) special_RHR();
            else if (counter == 4) {
              cross = 2;
              counter ++;
            }
            break;
          }
        }
      }
      //...............................................................................line changing
      mi1 = millis ();
    }
    //................................................................end of sum=4

    //...........................................................................sum=6
    else if (sum == 6 && mode == 1) {
      digitalWrite(d30, HIGH);
      digitalWrite(d90, HIGH);
      k30 = 0;
      mov = 1;
      k90 = 1;
      m81 = m82 = millis();
      while (sum != 0) {
        check();
        m82 = millis();
        if (m82 - m81 >= 120) {
          if (sum == 6 && counter == 100) {
            braking_mechanism();
            motorSpeedS();
            while (sum == 6) {
              check();
              text_battery_check();
              if (digitalRead(calin) == HIGH) break;
            }
            text_line_follow();
            break;
          }
          else {
            mov = 0;
            if (counter == 7 || counter == 8 || counter == 9) {
              counter = 9;
              cross = 2;              
            }
            break;
          }
        }
      }
      digitalWrite(d30, LOW);
      digitalWrite(d90, LOW);
      mi1 = millis();
    }


    mi2 = millis();
    if (mi2 - mi1 >= 200 || counter == 1)  mov = 0; //500ms por movement automatic 0 korar command

  }//end of while loop!!!!!
}//line following function
