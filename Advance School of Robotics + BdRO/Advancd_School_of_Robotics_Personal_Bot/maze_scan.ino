void maze_scan(bool initial) {
  while (digitalRead(sw)) { //infinite loop
a:    reading();
    if (sum == 0) {
      if (flag != 's') {
        braking();
        (flag == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'l') ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
        pos = 0; flag = 's'; cross = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }

      else if (pos < 4 && pos > -4) {
        motor(10 * spl, 10 * spr); m3 = millis();
        while (sum == 0) {
          reading(); m2 = millis();
          if (m2 - m3 > u_turn_timer) {
            braking(); digitalWrite(head_light, HIGH);
            (side == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp);
            while (s[2] == 0 && s[3] == 0) reading();
            (side == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
            scan[counter] = 4; counter++;
            pos = 0; flag = 's'; cross = 0; break;
          }
        }
      }

    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 0) {
        braking();
        (cross == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[4] + s[3] + s[2] + s[1] > 0) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
        pos = 0; flag = 's'; cross = 0;
      }

      else if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * dr) : delay(-pos * dr); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr);
      }
      //right side portion
      else if (sensor == 0b000100) {
        motor(10 * spl, 9 * spr);
      }
      else if (sensor == 0b000110) {
        if (pos < 1)pos = 1; motor(10 * spl, 6 * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2)pos = 2; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3)pos = 3; motor(10 * spl, 0 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4; motor(10 * spl, -3 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) {
        motor(9 * spl, 10 * spr);
      }
      else if (sensor == 0b011000) {
        if (pos > -1)pos = -1; motor(6 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2)pos = -2; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3)pos = -3; motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        if (pos > -4)pos = -4; motor(-3 * spl, 10 * spr);
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) { //only for sharp turn logic
      if (s[0] == 0 && s[5] == 1 && s[2] + s[3] > 0) {
        flag = 'l';
        while (s[0] == 0 && s[5] == 1 && s[2] + s[3] > 0) reading();
        if (s[0] == 0) {
          delay(node_delay); reading();
          if (sum > 0) {
            if (side == 1) cross = 1;
            (side == 1) ? scan[counter] = 1 : scan[counter] = 2;
            counter ++; digitalWrite(head_light, HIGH);
          }
        }
      }
      else if (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) {
        flag = 'r';
        while (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) reading();
        if (s[5] == 0) {
          delay(node_delay); reading();
          if (sum > 0) {
            if (side == 2) cross = 2;
            (side == 2) ? scan[counter] = 3 : scan[counter] = 2;
            counter ++; digitalWrite(head_light, HIGH);
          }
        }
      }
      m1 = millis();
    }

    else if (sum == 6) {
      m3 = millis(); flag = 's'; cross = 0;
      while (s[0] == 1 || s[5] == 1) {
        reading(); m2 = millis();
        if (m2 - m3 > stop_timer) {
          braking();
          digitalWrite(red_light, 1); delay(1000);  digitalWrite(red_light, 0);
          scan[counter] = 5; algorithm();
          if (initial == 1) {
            motor(-100, 100); delay(return_delay);
            motor(100, -100); delay(tbr); motor(0, 0); delay(20);
            maze_solve(1);
          }
           digitalWrite(red_light, 0); return;
        }
      }
      if (m2 - m3 < stop_timer) {
        delay(node_delay); reading();
        if (sum == 0) (side == 1) ? flag = 'l' : flag = 'r';
        else (side == 1) ? cross = 1 : cross = 2;
        (side == 1) ? scan[counter] = 1 : scan[counter] = 3;
        counter ++; digitalWrite(head_light, HIGH);
      }
      m1 = millis();
    }
    m2 = millis();
    if (m2 - m1 > 200) {
      flag = 's'; digitalWrite(head_light, LOW);
    }
  }
}
