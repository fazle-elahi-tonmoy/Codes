void line_follow() {
  oled.clear(); oled.set2X(); counter = EEPROM.read(29); text("LineFollow", 04, 3);
  lefthand.write(lservo[0]);
  righthand.write(rservo[0]);
  delay(500);
  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
point:    reading();
    if (path[counter] == 7) {
      spl = 10 - le; spr = 10 - re;
      node = 100; br = 0; counter++;
    }
    if (sum == 0) {
      if (flag != 0 || cross != 0) {
        motor(-250, -250); delay(br);
        if (path[counter] == 4 || path[counter] == 5) grab(path[counter] - 3);
        else if (path[counter] == 9 || path[counter] == 8) grab(path[counter] - 7);
        else if (path[counter] == 10) drop(1, 0);
        else if (path[counter] == 11) counter++;
        (flag == 1 || cross == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp) ;
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 1 || cross == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp) ;
        delay(tbr); pos = 0; flag = 0; cross = 0;
      }
      else if (pos < 4 && pos > -4) {
        m1 = millis(); motor(40, 40);
        while (sum == 0) {
          m2 = millis(); reading();
          if (m2 - m1 > epoint) {
            motor(-250, -250); delay(br);
            if (path[counter] == 4 || path[counter] == 5) grab(path[counter] - 3);
            else if (path[counter] == 9 || path[counter] == 8) grab(path[counter] - 7);
            else if (path[counter] == 10) drop(1, 1);
            else if (path[counter] == 11) counter++;
            motor(0, 0); delay(100);
            motor(-tsp, tsp);
            while (s[2] == 0 && s[3] == 0) reading();
            motor(tsp, -tsp); delay(tbr); pos = -4;
          }
        }
      }
    }
    else if (sum == 1 || sum == 2) {
      if (cross != 0) {
        motor(-250, -250); delay(br);
        if (path[counter] == 4 || path[counter] == 5) grab(path[counter] - 3);
        (cross == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[1] == 1 || s[2] == 1 || s[3] == 1 || s[4] == 1) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp);
        delay(tbr); pos = 0; cross = 0;
      }
      else if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * dt) : delay(-pos * dt); pos = 0;
        }
        motor(10 * spl, 10 * spr);
      }
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1;
        motor(10 * spl, 7 * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2;
        motor(10 * spl, 5 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3;
        motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4;
        motor(10 * spl, 0 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1;
        motor(6 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2;
        motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3;
        motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4;
        motor(-3 * spl, 10 * spr);
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) { //only for sharp turn logic
      m1 = millis(); motor(40, 40);
      if (s[5] == 1 && s[0] == 0 && (s[3] == 1 || s[2] == 1)) {
        flag = 1;
        if (path[counter] != 2) {
          while (sum < 6 && sum > 0) {
            reading(); m2 = millis();
            if (m2 - m1 > node) {
              if (path[counter] == 1) cross = 1;
              counter ++;
              if (path[counter] == 6) drop(0, 0);
              else if (path[counter - 1] == 3 && path[counter] > 3 && path[counter] < 6) grab(path[counter] - 3);
              digitalWrite(light, 1); break;
            }
          }
        }
      }
      else if (s[5] == 0 && s[0] == 1 && (s[3] == 1 || s[2] == 1)) {
        flag = 2;
        if (path[counter] != 1) {
          while (sum < 6 && sum > 0) {
            reading(); m2 = millis();
            if (m2 - m1 > node) {
              if (path[counter] == 2) cross = 2;
              counter ++;
              if (path[counter] == 6) drop(0, 0);
              else if (path[counter - 1] == 3 && path[counter] > 3 && path[counter] < 6) grab(path[counter] - 3);
              digitalWrite(light, 1); break;
            }
          }
        }
      }
      m3 = millis();
    }

    else if (sum == 6) {
      m1 = millis(); motor(40, 40);
      while (sum > 0) {
        reading(); m2 = millis();
        if (m2 - m1 > node) {
          motor(0, 0);
          if (sum == 6) {
            while (sum == 6 && digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) reading();
            if (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) {
              delay(1000); goto point;
            }
          }
          break;
        }
      }
      if (path[counter] == 1) cross = 1;
      else if (path[counter] == 2) cross = 2;
      counter ++;
      if (path[counter] == 6) drop(0, 0);
      else if (path[counter - 1] == 3 && path[counter] > 3 && path[counter] < 6) grab(path[counter] - 3);
      flag = 0; digitalWrite(light, 1); m3 = millis();
    }
    m2 = millis();
    if (m2 - m3 > 200) {
      flag = 0; digitalWrite(light, 0);
    }
  }
  intro();  motor(0, 0); digitalWrite(light, 0); cross = 0; flag = 0;
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}
