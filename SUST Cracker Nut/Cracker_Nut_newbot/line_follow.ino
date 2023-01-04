void line_follow() {
  while (digitalRead(swl) == HIGH) {
    check();
    inverse_y();
    if (sum == 0) {
      if (mov == 1 ) {
        if (k30 == 1) {
          digitalWrite(blue, HIGH);
          braking_mechanism();
          while (sum == 0) {
            check();
            motorSpeedR(tsp, tsp);
          }
          if (br != 0) motorSpeedL(tsp, tsp);
          delay(br);
          digitalWrite(blue, LOW);
        }
        else if (k90 == 1) {
          digitalWrite(green, HIGH);
          braking_mechanism();
          while (sum == 0) {
            check();
            motorSpeedR(tsp, tsp);

          }
          if (br != 0) motorSpeedL(tsp, tsp);
          delay(br);
          digitalWrite(green, LOW);
        }
        if (tcount == 1) {
          tcount = 0; counter ++;
        }
      }
      else if (mov == 2) {
        if (k30 == 2) {
          digitalWrite(blue, HIGH);
          braking_mechanism();
          while (sum == 0) {
            check();
            motorSpeedL(tsp, tsp);
          }
          if (br != 0) motorSpeedR(tsp, tsp);
          delay(br);
          mos(50, 50);
          digitalWrite(blue, LOW);
        }
        else if (k90 == 2) {
          digitalWrite(green, HIGH);
          braking_mechanism();
          while (sum == 0) {
            check();
            motorSpeedL(tsp, tsp);
          }
          if (br != 0) motorSpeedR(tsp, tsp);
          delay(br);
          mos(50, 50);
          digitalWrite(green, LOW);
          if (tcount == 1) {
            tcount = 0; counter ++;
          }
        }
      }
      else if (mov == 0 && k < 4 && k > -4) {
        mos(50, 50);
        m81 = m82 = millis();
        while (sum == 0) {
          m82 = millis(); check();
          if (wall_trigger(2) == 1 && midpoint != 0) wall_follow();
          if (m82 - m81 > mtd) {
            braking_mechanism();
            digitalWrite(red, HIGH); digitalWrite(green, HIGH); digitalWrite(blue, HIGH);
            (side == 1) ? motorSpeedR(tsp, tsp) : motorSpeedL(tsp, tsp);
            while (sensor[4] == 0 && sensor [3] == 0) check();
            (side == 1) ? motorSpeedL(tsp, tsp) : motorSpeedR(tsp, tsp);
            delay(br);
            digitalWrite(red, LOW); digitalWrite(green, LOW); digitalWrite(blue, LOW);
          }
        }
      }
    }//.................................................................end of sum 0

    //..............................................................sum=1||sum=2
    else if (sum == 1 || sum == 2) {
      if (object_boundary != 0) obstacle(1);
      else if (cross == 1) {
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);
        braking_mechanism();
        motorSpeedR(tsp, tsp);
        check();
        while (sensor[0] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedL(tsp, tsp);
        delay(br);
        mos(50, 50);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      else if (cross == 2) {
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
        braking_mechanism();
        motorSpeedL(tsp, tsp);
        while (sensor[5] == 0) check();
        while (sensor[2] == 1 || sensor[3] == 1) check();
        while (sensor[2] == 0 && sensor[3] == 0) check();
        motorSpeedR(tsp, tsp);
        delay(br);
        mos(50, 50);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      //.............................................................line shuru
      else if (bin == 12) {
        if (k > 0) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(k * 6);
        }
        else if (k < 0) {
          k = -k;
          motorSpeedR(10 * spr, 10 * spl);
          delay(k * 6);
        }
        k = 0;
        mos(10 * spr, 10 * spl);
        if (cl < peak) cl++;
      }
      else if (bin == 4) {
        mos(9 * spr, 10 * spl);
        if (cl < peak) cl++;
      }

      else if (bin == 8) {
        mos(10 * spr, 9 * spl);
        if (cl < peak) cl++;
      }
      //..................................................left side position
      else if (bin == 6) {
        if (k < 2) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 2;
        }
        mos(6 * spr, 10 * spl);
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
        mos( 0 * spr, 10 * spl);
        //mov = 1;
      }
      else if (bin == 1) {
        if (k < 5) {
          motorSpeedR(10 * spr, 10 * spl);
          delay(dt);
          k = 5;
        }
        mos(-3 * spr, 10 * spl);
      }
      // ..................................................dan side shesh
      // .....................................................bam side shuru
      else if (bin == 24) {
        if (k > -2) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -2;
        }
        mos(10 * spr, 6 * spl);
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
        mos(10 * spr, 0 * spl);
        //mov = 2;
      }
      else if (bin == 32) {
        if (k > -5) {
          motorSpeedL(10 * spr, 10 * spl);
          delay(dt);
          k = -5;
        }
        mos(10 * spr, -3 * spl);
      }
    }//...........................................................................end sum 1
    //...............................................................................sum=3||sum=4||sum=5
    else if (sum == 3 || sum == 4 || sum == 5) {
      tcount = 0;
      mos(50, 50);
      if (sensor[0] == 1 && sensor [1] == 0 && (sensor [2] == 1 || sensor [3] == 1) ) {
        k30 = 1;
        mov = 1;
      }

      else if (sensor [5] == 1 && sensor [4] == 0 && (sensor [2] == 1 || sensor [3] == 1)) {
        k30 = 2;
        mov = 2;
      }

      else if (bin == 7 || bin == 15 || bin == 31) { //31 mane 011111
        k90 = 1;
        mov = 1;
        if (side == 1) {
          while (sensor[0] == 1 && sensor [5] == 0) check();
          if (sensor [5] == 0 && sum != 0) {
            delay(ltd); cross = 1;
          }
        }
      }
      else if (bin == 56 || bin == 60 || bin == 62) {   //62 mane 111110
        k90 = 2;
        mov = 2;
        if (side == 2) {
          while (sensor[5] == 1 && sensor [0] == 0) check();
          if (sensor [0] == 0 && sum != 0) {
            delay(ltd); cross = 2;
          }
        }
      }
      //...............................................................................line changing
      mi1 = millis ();
    }
    //................................................................end of sum=4

    //...........................................................................sum=6
    else if (sum == 6 && mode == 1) {
      mos(50, 50);
      digitalWrite(red, HIGH);
      k30 = 0;
      //      tcount = 1;
      (side == 1) ? mov = 1 : mov = 2;
      (side == 1) ? k90 = 1 : k90 = 2;
      m81 = m82 = millis();
      while (sensor [0] == 1 || sensor [5] == 1) {
        check();
        m82 = millis();
        if (m82 - m81 >= 100) {
          braking_mechanism();
          motorSpeedS();
          while (sum == 6) {
            check();
            if (digitalRead(swl) == LOW) break;
          }
          text_line_follow();
          break;
        }
      }
      if (m82 - m81 < 100) {
        if (sum != 0) {
          delay(ltd); check();
          if (side == 1)  cross = 1 ;
          else if (side == 2) cross = 2;
        }
      }
      digitalWrite(red, LOW);
      mi1 = millis();
    }


    mi2 = millis();
    if (mi2 - mi1 >= 300) {
      tcount = 0;
      mov = 0;
    }

  }//end of while loop!!!!!
  cross = 0;
  mov = 0;
}//line following function
