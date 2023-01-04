void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (sum == 0) {
    sonar();
    check();
    m82 = m81 = millis();
    if (flag == 1) {
      if (sl < 12 && sl > 5) mos(0, 150);
      else if (sl > 16 && sl <= 40) mos(150, 0);
      else mos(6 * spr, 6 * spl);
    }

    else if (flag == 0) {
      if (sr < 12 && sr > 5) mos(150, 0);
      else if (sr > 16 && sr <= 40) mos(0, 150);
      else if (sr >= 13 && sr <= 15) mos(6 * spr, 6 * spl);
      else {
        while ((sr < 5 || sr > 30) && sl <= 40 && sl > 5) {
          sonar();
          m82 = millis();
          if (m82 - m81 >= 50) {
            flag = 1;
            break;
          }
        }
      }
    }

  }
  digitalWrite(calout, LOW);
//  spr=20;
//  spl=23;
  }





void wall_function() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    m82 = m81 = millis();
    if (flag == 0) {
      if (sl < 12 && sl > 5) mos(0, 150);
      else if (sl > 16 && sl <= 40) mos(150, 0);
      else if (sl >= 13 && sl <= 15) mos(6 * spr, 6 * spl);
      else {
        while ((sl < 5 || sl > 40) && sr <= 40 && sr > 5) {
          sonar();
          m82 = millis();
          if (m82 - m81 >= 100) {
            flag = 1;
            break;
          }
        }
      }
    }

    else if (flag == 1) {
      if (sr < 12 && sr > 5) mos(150, 0);
      else if (sr > 16 && sr <= 40) mos(0, 150);
      else mos(6 * spr, 6 * spl);
    }

  }
  digitalWrite(calout, LOW);
}
