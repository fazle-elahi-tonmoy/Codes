void maze_solve(bool solve_from_finish) {
  memory_recall();
  if (solve_from_finish) counter = solving_pattern();
  else counter = 0;

  while (1) {
    reading();
    if (sum == 0) {
      if (turn != 's') {
        (turn == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);
        while (!s[2] && !s[3]) reading();
        turn = 's';
      }
    }

    else if (sum == 1 || sum == 2) {
      if (cross != 's') {  //turn from one line to another
        (cross == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);
        while (s[1] + s[2] + s[3] + s[4]) reading();
        while (!s[2] && !s[3]) reading();
        cross = 's';
      }
      if (sensor == 0b001100) motor(10 * spl, 10 * spr);
      //left side
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) motor(6 * spl, 10 * spr);
      else if (sensor == 0b010000) motor(3 * spl, 10 * spr);
      else if (sensor == 0b110000) motor(0 * spl, 10 * spr);
      else if (sensor == 0b100000) motor(-3 * spl, 10 * spr);
      //right side
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) motor(10 * spl, 6 * spr);
      else if (sensor == 0b000010) motor(10 * spl, 3 * spr);
      else if (sensor == 0b000011) motor(10 * spl, 0 * spr);
      else if (sensor == 0b000001) motor(10 * spl, -3 * spr);
    }

    else if (sum >= 3 && sum <= 5) {
      if (!s[5] && s[0] && s[2] + s[3]) {
        turn = 'r';
        while (!s[5] && s[0]) reading();  //verifying if it is relly right turn or T section
        if (!s[0]) {                      //if it is really right turn
          delay(node_delay);
          reading();
          if (sum) {
            if (path[counter] == 3) cross = 'r';
            (solve_from_finish) ? counter-- : counter++;
            digitalWrite(led, 1);
          }
        }
      }

      if (!s[0] && s[5] && s[2] + s[3]) {
        turn = 'l';
        while (!s[0] && s[5]) reading();  //verifying if it is relly left turn or T section
        if (!s[5]) {                      //if it is really left turn
          delay(node_delay);
          reading();
          if (sum) {
            if (path[counter] == 1) cross = 'l';
            (solve_from_finish) ? counter-- : counter++;
            digitalWrite(led, 1);
          }
        }
      }
      m2 = millis();  //timer reset for turn
    }

    else if (sum == 6) {
      m1 = millis();  //timer reset
      while (sum == 6) {
        reading();
        if (millis() - m1 >= stop_timer) {
          motor(0, 0);
          return;
        }
      }
      delay(node_delay);
      reading();

      if (path[counter] == 1) turn = 'l';  //T section
      else if (path[counter] == 3) turn = 'r';

      if (sum) {  //cross section
        if (path[counter] == 1) cross = 'l';
        else if (path[counter] == 3) cross = 'r';
      }

      (solve_from_finish) ? counter-- : counter++;
      digitalWrite(led, 1);
      m2 = millis();  //timer reset for turn
    }

    if (millis() - m2 > 500) {
      turn = 's';
      digitalWrite(led, 0);
    }
  }  //while 1
}  //void line follow