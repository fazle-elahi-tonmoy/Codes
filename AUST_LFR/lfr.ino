void line_follow() {
  while (1) {
    reading();
    if (sum == 0) {  //sharp turn execution
      if (turn != 's') {
        delay(node_delay);                                    // adjust it to your needs!
        (turn == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);  //tsp means turn speed. adjust it to your needs!
        while (!s[2] && !s[3]) reading();                     //keep turning untill the middle sensors find any line
        turn = 's';                                           //reset the flag so that robot won't do any fake turn
      }
    }

    else if (sum == 1 || sum == 2) {  //normal line
      if (cross != 's') {
        (cross == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);
        while (s[1] + s[2] + s[3] + s[4]) reading();
        while (!s[1] && !s[2] && !s[3] && !s[4]) reading();
        cross = turn = 's';
      }
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * lsp, 10 * rsp) : motor(10 * lsp, -10 * rsp);
          delay(abs(pos) * 2);  //adjust it to your needs. you can multiply with 3,4,5 or 6
        }
        motor(10 * lsp, 10 * rsp);
      }

      //for right side turn correction
      else if (sensor == 0b000100)
        motor(10 * lsp, 9 * rsp);

      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1;
        motor(10 * lsp, 6 * rsp);  //line_prop must be a float value
      }

      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2;
        motor(10 * lsp, 3 * rsp);
      }

      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3;
        motor(10 * lsp, 0 * rsp);
      }

      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4;
        motor(10 * lsp, -3 * rsp);
      }

      //for left side turn detection
      else if (sensor == 0b001000)
        motor(9 * lsp, 10 * rsp);

      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1;
        motor(6 * lsp, 10 * rsp);
      }

      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2;
        motor(3 * lsp, 10 * rsp);
      }

      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3;
        motor(0 * lsp, 10 * rsp);
      }

      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4;
        motor(-3 * lsp, 10 * rsp);
      }
    }

    else if (sum >= 3 && sum <= 5) {  //sharp turn detection
      if ((s[2] + s[3]) && s[0] && !s[5]) {
        turn = 'r';
        if (side == 'r') {
          while (s[0] && !s[5]) reading();
          if (!s[5]) {
            delay(node_delay);
            reading();
            if (sum != 0) cross = 'r';
          }
        }
      }

      if ((s[2] + s[3]) && s[5] && !s[0]) {
        turn = 'l';
        if (side == 'l') {
          while (s[5] && !s[0]) reading();
          if (!s[0]) {
            delay(node_delay);
            reading();
            if (sum != 0) cross = 'l';
          }
        }
      }
      t1 = millis();
    }

    else if (sum == 6) {
      t2 = millis();
      while (sum == 6) {
        reading();
        if (millis() - t2 > 200) {
          motor(0, 0);
          while (sum == 6) reading();
        }
      }
      delay(node_delay);
      reading();
      if (sum == 0) turn = 'r';
      else if (sum > 0) turn = 's';
      t1 = millis();
    }
    if (millis() - t1 > 200) turn = 's';
  }
}