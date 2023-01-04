void fixed_path() {
  counter = 0;
  while (1) { //infinite loop
    reading();
    if (sum == 0) {
      if (flag != 's') {
        (flag == 'l') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
        delay(turn_brake);
        flag = 's'; cross = 's'; pos = 0;//when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
      else if (pos < 4 && pos > -4) {
        m1 = millis();
        while (sum == 0) {
          reading();
          if (millis() - m1 > u_turn_timer) {
            (side == 1) ? flag = 'l' : flag = 'r';
            digitalWrite(led, 1); m2 = millis();
            break;
          }
        }
      }
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 's') {
        (cross == 'l') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
        while (s[1] + s[2] + s[3] + s[4]) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 'r') ? motor(-turn_speed, turn_speed) :  motor(turn_speed, -turn_speed);
        delay(turn_brake); cross = 's'; flag = 's';
      }
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ?  motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * 5) : delay(-pos * 5); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr);
      }
      //right side portion
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1; motor(10 * spl, 6 * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3; motor(10 * spl, 0 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4;
        motor(10 * spl, -3 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1; motor(6 * spl, 10 * spr);
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
      if (s[0] && (s[2] || s[3]) && !s[5]) {
        flag = 'r';
        while (s[0] && !s[5]) reading();
        if (!s[5]) {
          delay(node_delay); reading();
          if (sum) {
            if (scan[counter] == 3) cross = 'r';
            counter++; digitalWrite(led, 1);
          }
        }
      }
      else if (s[5] && (s[2] || s[3]) && !s[0]) {
        flag = 'l';
        while (s[5] && !s[0]) reading();
        if (!s[0]) {
          delay(node_delay); reading();
          if (sum) {
            if (scan[counter] == 1) cross = 'l';
            counter++; digitalWrite(led, 1);
          }
        }
      }
      m2 = millis();
    }

    else if (sum == 6) {
      m1 = millis();
      while (s[0] || s[5]) {
        reading();
        if (millis() - m1 > stop_timer) {
          motor(0, 0);
          digitalWrite(led, 0); cross = 's'; flag = 's'; pos = 0;
          return;
        }
      }
      (scan[counter] == 1) ? flag = 'l' : flag = 'r';
      delay(node_delay); reading();
      if (sum != 0) {
        if (scan[counter] == 1) cross = 'l' ;
        else if (scan[counter] == 3) cross = 'r';
      }
      counter ++;
      digitalWrite(led, 1); m2 = millis();
    }

    if (millis() - m2 > 250) {
      flag = 's'; digitalWrite(led, 0);
    }
  }
}
