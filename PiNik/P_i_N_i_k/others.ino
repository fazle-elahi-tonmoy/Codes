void maze_func() {
  byte t = 0, cl = 0, list = 4, m = 1, flag = 0;
  while (1) {
    if (cl != m) {
      cl = m;
      display.clearDisplay();
      if (cl == 1) {
        text("MAZE SCAN", 10, 12);
        text("  RETURN  ", 04, 38);
      }
      else if (cl == 2) {
        text("MAZE SCAN", 10, 12);
        text("   STOP   ", 04, 38);
      }
      else if (cl == 3) {
        text("MAZE SOLVE", 04, 12);
        text("FROM START", 04, 38);
      }
      else if (cl == 4) {
        text("MAZE SOLVE", 04, 12);
        text(" FROM END ", 04, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && m < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); m++;
    }
    else if (digitalRead(db) == LOW && m > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); m--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) return;
      if (cl == 1) line_follow(1, 1);
      else if (cl == 2) line_follow(1, 0);
      else if (cl == 3) line_solve(1, 0);
      else if (cl == 4) line_solve(1, 1);
      while (digitalRead(mb) == LOW);
      return;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}

void control_system() {
  byte  cl = 0, list = 7, m = 1, flag = 0;
  while (1) {
    if (cl != m) {
      cl = m;
      display.clearDisplay();
      if (cl == 1) text("HEADLIGHT", 11, 25);
      else if (cl == 2) {
        text("  FANG?  ", 10, 12);
        (fang == 0) ? text("  CLOSE  ", 10, 38) : text("   OPEN   ", 4, 38);
      }
      else if (cl == 3) {
        text("BLUETOOTH", 11, 12);
        text("CONTROL", 23, 38);
      }
      else if (cl == 4) {
        text("WALL TRIG?", 04, 12);
        (trigger == 1) ? text("  RIGHT  ", 10, 38) : text("   LEFT   ", 4, 38);
      }
      else if (cl == 5) {
        text(" OBSTACLE ", 04, 0);
        text("DIRECTION", 10, 25);
        (o_direction == 1) ? text("  RIGHT  ", 10, 50) : text("   LEFT   ", 4, 50);
      }
      else if (cl == 6) {
        text("  MOTOR  ", 10, 12);
        text("DIRECTION", 10, 38);
      }
      else if(cl == 7){
        text("  SNAKE  ", 10, 12);
        text("   GAME   ", 04, 38);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW && m < list) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); m++;
    }
    else if (digitalRead(db) == LOW && m > 1) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      m81 = millis(); m--;
    }
    else if (digitalRead(mb) == LOW) {
      if (long_press(0) == 1) return;
      if (cl == 1) light_control();
      else if (cl == 2) fang_selection();
      else if (cl == 3) remote_control();
      else if (cl == 4) side_selection(2);
      else if (cl == 5) side_selection(1);
      else if (cl == 6) motor_direction();
      else if (cl == 7) snake_game();
      while (digitalRead(mb) == LOW);
      cl = 0;
    }
    m82 = millis();
    if (m82 - m81 > 25) flag = 0;
  }
}

void fang_selection() {
  byte cl = 2;
  while (digitalRead(mb) == HIGH) {
    if (cl != fang) {
      cl = fang;
      display.clearDisplay();
      if (cl == 1) {
        text("   OPEN   ", 4, 25);
        lfang.write(fl);
        rfang.write(fr);
      }
      else if (cl == 0) {
        text("  CLOSE  ", 10, 25);
        lfang.write(intl);
        rfang.write(intr);
      }
      display.display();
    }
    if (digitalRead(ub) == LOW) fang = 1;
    else if (digitalRead(db) == LOW) fang = 0;
  }
  while (digitalRead(mb) == LOW);
  state = fang * 10 + head;
  EEPROM.write(10, state); delay(10);
}

void light_control() {
  byte cl = 2;
  while (digitalRead(mb) == HIGH) {
    if (cl != head) {
      cl = head;
      display.clearDisplay();
      (cl == 1) ? text("    ON    ", 4, 25) : text("   OFF   ", 10, 25);
      head_light(cl);
      display.display();
    }
    if (digitalRead(ub) == LOW) head = 1;
    else if (digitalRead(db) == LOW) head = 0;
  }
  while (digitalRead(mb) == LOW);
  state = fang * 10 + head;
  EEPROM.write(10, state); delay(10);
}

void side_selection(byte a) {
  byte cl = -1, temp[3];
  temp[0] = direct / 100; temp[1] = (direct % 100) / 10; temp[2] = direct % 10;
p: if (temp[a] == 0) {
    display.clearDisplay();
    text(" STRAIGHT ", 4, 25);
    display.display();
    while (digitalRead(ub) == LOW || digitalRead(db) == LOW) delay(1);
  }
  while (digitalRead(mb) == HIGH) {
    if (cl != temp[a] && temp[a] != 0) {
      cl = temp[a];
      display.clearDisplay();
      (cl == 1) ? text("  RIGHT  ", 10, 25) : text("   LEFT   ", 4, 25);
      display.display();
    }
    if (digitalRead(ub) == LOW && digitalRead(db) == LOW && a == 0) {
      temp[a] = 0;
      goto p;
    }
    else if (digitalRead(ub) == LOW) temp[a] = 1;
    else if (digitalRead(db) == LOW) temp[a] = 2;
  }
  while (digitalRead(mb) == LOW);
  direct = temp[0] * 100 + temp[1] * 10 + temp[2];
  EEPROM.write(9, direct); delay(10);
  side = temp[0]; o_direction = temp[1]; trigger = temp[2];
}
