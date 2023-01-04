void line_follow() {
  while (digitalRead(calin) == LOW) {
    check();
    //    if (sensor[0] == 1 && sensor[5] == 1 && (sensor[1] == 0 || sensor[2] == 0 || sensor[3] == 0 || sensor[4] == 0)) {
    //      if (counter == 1 && mode == 1) {
    //        mode = 0;
    //        digitalWrite(calout, HIGH);
    //      }
    //      else if (counter == 1 && mode == 0) {
    //        mode = 1;
    //        counter = 2;
    //        btd = 50;
    //        digitalWrite(calout, LOW);
    //      }
    //      else if (counter == 2) y_section();
    //    }

    if (sum == 0) {
      if (tcount == 1) {
        tcount = 2;
        counter = 1;
        spl = 25;
        spr = 22;
        btd = 50;
      }
      if (mov == 1 ) {
        delay(btd);
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
        delay(btd);
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

      //      else if (mov == 0) {
      //        m81 = m82 = millis();
      //        while (sum == 0) {
      //          check();
      //          m82 = millis();
      //          else if (m82 - m81 >= mtd) {
      //            digitalWrite(13, HIGH);
      //            motorSpeedB(10 * spr, 10 * spl);
      //            brake = cl / d;
      //            delay(brake);
      //            while (bin != 12) {
      //              check();
      //              motorSpeedL(4 * spr, 4 * spl);
      //            }
      //            motorSpeedR(4 * spr, 4 * spl);
      //            delay(br);
      //            k90 = 0;
      //            mov = 0;
      //            cl = base;
      //            brake = cl / d;
      //            k = 0;
      //            digitalWrite(13, LOW);
      //            break;
      //          }
      //        }
      //      }
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      check();
      if (cross == 1) {
        cross = 0;
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        motorSpeedB(10 * spr, 10 * spl);
        brake = cl / d;
        delay(brake);
        while (sensor[1] == 1 || sensor[2] == 1 || sensor[3] == 1 || sensor[4] == 1) {
          check();
          motorSpeedR(6 * spr, 6 * spl);
        }
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
        digitalWrite(d30, LOW);
      }
      if (cross == 2) {
        cross = 0;
        digitalWrite(d90, HIGH);
        digitalWrite(d30, HIGH);
        motorSpeedB(10 * spr, 10 * spl);
        brake = cl / d;
        delay(brake);
        while (sensor[1] == 1 || sensor[2] == 1 || sensor[3] == 1 || sensor[4] == 1) {
          check();
          motorSpeedL(6 * spr, 6 * spl);
        }
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
        digitalWrite(d30, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 0) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
        }
        else if (k < 0) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
        }
        k = 0;
        mos(10 * spr, 10 * spl);
        cl++;
        if (cl > peak) cl = peak;
      }
      else if (bin == 4) {
        mos(9 * spr, 10 * spl);
        cl++;
        if (cl > peak) cl = peak;
      }

      else if (bin == 8) {
        mos(10 * spr, 9 * spl);
        cl++;
        if (cl > peak) cl = peak;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 2;
        }
        mos(7 * spr, 10 * spl);
      }
      else if (bin == 2) {
        if (k < 3) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 3;
        }
        mos(4.5 * spr, 10 * spl);
      }
      else if (bin == 3) {
        if (k < 4) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 4;
        }
        mos( -3 * spr, 10 * spl);
        mov = 1;
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
        mos(10 * spr, 7 * spl);
      }
      else if (bin == 16) {
        if (k > -3) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -3;
        }
        mos(10 * spr, 4.5 * spl);
      }
      else if (bin == 48) {
        if (k > -4) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -4;
        }
        mos(10 * spr, -3 * spl);
        mov = 2;
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

      else if (bin == 33 && counter >= 2) y_section();
    }//...........................................................................end sum 1

    //..............................................................................sum=3
    else if (sum == 3) {
      if (bin == 11 || bin == 13 || bin == 9 || bin == 25 || bin == 19) {
        k30 = 1;
        mov = 1;
      }

      else if ( bin == 52 || bin == 44 || bin == 36 || bin == 38 || bin == 50) {
        k30 = 2;
        mov = 2;
      }

      else if (bin == 7) {
        k90 = 1;
        mov = 1;
      }

      else if (bin == 56) {
        mov = 2;
        k90 = 2;
        if (counter >= 2 && mode == 1) {
          m81 = m82 = millis();
          while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
            check();
            m82 = millis();
            if (m82 - m81 >= 120) {
              cross = 2;
              break;
            }
          }
        }
      }

      //      else if (bin == 35 || bin == 49) y_section();

      mi1 = millis();

    }// ...................................................................end of sum=3

    //...............................................................................sum=4||sum=5
    else if (sum == 4 || sum == 5) {
      if (  bin == 15 || bin == 31) { //31 mane 011111
        k90 = 1;
        mov = 1;
      }
      else if (  bin == 60 || bin == 62) {   //62 mane 111110
        k90 = 2;
        mov = 2;
        if (counter >= 2 && mode == 1) {
          m81 = m82 = millis();
          while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
            check();
            m82 = millis();
            if (m82 - m81 >= 120) {
              cross = 2;
              break;
            }
          }
        }
      }
      //...............................................................................line changing
      else if ((bin == 51 || bin == 39 || bin == 57 || bin == 59 || bin == 55) && counter == 1) {
        if (mode == 1) {
          mode = 0;
          spl = 18;
          spr = 15;
          btd = 80;
          digitalWrite(calout, HIGH);
        }
        else {
          mode = 1;
          spl = 25;
          spr = 22;
          counter = 2;
          btd = 50;
          digitalWrite(calout, LOW);
        }
      }
      else if ((bin == 51 || bin == 39 || bin == 57) && counter == 2) y_section();
      mi1 = millis ();
    }
    //................................................................end of sum=4

    //...........................................................................sum=6
    else if (sum == 6) {
      digitalWrite(d30, HIGH);
      digitalWrite(d90, HIGH);
      cross = 0;
      k30 = 0;
      mov = 2;
      k90 = 2;
      //      if (counter == 0 || counter == 2) {
      //        mov = 2;
      //        k90 = 2;
      //      }
      //      else if (counter == 1) {
      //        mov = 1;
      //        k90 = 1;
      //      }
      if (tcount == 0) tcount = 1;
      m81 = m82 = millis();
      while (sum == 5 || sum == 6 || sum == 4 || sum == 3 || sum == 2 || sum == 1) {
        check();
        m82 = millis();
        if (m82 - m81 >= 150) {
          if (sum == 6 && mode == 1) {
            motorSpeedB(10 * spr, 10 * spl);
            brake = cl / d;
            delay(brake);
            k90 = 0;
            mov = 0;
            cl = base;
            brake = cl / d;
            mov = 0;
            k30 = 0;
            k90 = 0;
            cross = 0;
            motorSpeedS();
            text_battery_check();
            for (int i = 0; digitalRead(calin) == LOW; i++) {
              delay(1);
              if (i == 2000) break;
            }
            text_line_follow();
            break;
          }
          else if (sum == 6 && mode == 0) {
            digitalWrite(calout, LOW);
            mode = 1;
            check();
            motorSpeedB(6 * spr, 6 * spl);
            //delay(brake);
            while (sensor[0] == 0 && sensor[5] == 0) check();
            motorSpeedL(6 * spr, 6 * spl);
            while (sensor[2] == 0 || sensor[3] == 0) check();
            motorSpeedR(6 * spr, 6 * spl);
            delay(br);
            counter = 2;
            spl = 25;
            spr = 22;
            btd = 50;
            digitalWrite(calout, LOW);
            break;
          }
          else {
            if (counter >= 1) cross = 2;
            break;
          }
        }
      }
      digitalWrite(d30, LOW);
      digitalWrite(d90, LOW);
      mi1 = millis();
    }


    mi2 = millis();
    if (mi2 - mi1 >= 1000) {
      mov = 0;
      if (tcount == 1) tcount = 0; //500ms por movement automatic 0 korar command
    }

  }//end of while loop!!!!!
}//line following function
