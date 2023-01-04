void line_follow() {
  while (1) { //infinite loop
p:    reading();
    if (sum == 0) {
      if (flag != 's') {
        brake();
        (flag == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-tsp, tsp) : motor(tsp, -tsp); delay(tbr);
        flag = 's'; pos = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 's') {
        brake(); digitalWrite(head_light, 1);
        (cross == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[1] + s[2] + s[3] + s[4]) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 'r') ? motor(-tsp, tsp) : motor(tsp, -tsp); delay(tbr);
        digitalWrite(head_light, 0);
        flag = 's'; cross = 's'; pos = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(5 * pos) : delay(-5 * pos); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
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
        pos = 4; motor(10 * spl, -3 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1; motor(6 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3; motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        pos = -4; motor(-3 * spl, 10 * spr);
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) { //only for sharp turn logic
      if (s[5] && (s[2] || s[3])) {
        flag = 'l';
        while (s[5] && !s[0]) reading();
        if (!s[0]) {
          delay(node_delay); reading();
          if (sum) cross = 'l';
        }
      }
      else if (s[0] && (s[2] || s[3])) flag = 'r';
      m1 = millis();
    }

    else if (sum == 6) {
      m2 = millis();
      while (s[0] || s[5]) {
        reading();
        if (millis() - m2 > stp_timer) {
          brake(); motor(0, 0);
          while (s[0] || s[5])reading();
          delay(1000); goto p;
        }
      }
      flag = 'l';
      delay(node_delay); reading();
      if (sum) { //cross section detector
        cross = 'l';
      }
      m1 = millis();
    }
    if (millis() - m1 > 300) flag = 's';
  }
}
