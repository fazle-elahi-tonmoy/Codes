void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (sum == 0) {
    sonar();
    check();
    if (sf <= 13 && sf > 5) {
      motorSpeedB(6 * spr, 6 * spl);
      delay(90);
      digitalWrite(d90, HIGH);
      digitalWrite(d30, HIGH);
      (sl <= 30 && sl >= 5) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
      delay(400);
      (sl <= 30 && sl >= 5) ? motorSpeedL(6 * spr, 6 * spl) : motorSpeedR(6 * spr, 6 * spl);
      delay(50);
      while (flag = 0) {
        sonar();
        mos(6 * spr, 6 * spl);
        if ((sl <= 30 && sl >= 5) || (sr <= 30 && sr >= 5)) {
          m82 = m81 = millis();
          while ((sl <= 30 && sl >= 5) || (sr <= 30 && sr >= 5)) {
            sonar();
            m82 = millis();
            if (m82 - m81 >= 50) {
              flag = 1;
              break;
            }
          }
        }
      }
      flag = 0;
      sf = 0;
      digitalWrite(d90, LOW);
      digitalWrite(d30, LOW);
    }

    else if (sl <= midpoint-2 && sl > 5) mos(50, 200);
    else if (sl >= midpoint+2 && sl <= 30) mos(200, 50);
    else if (sr <= midpoint-2 && sr > 5) mos(200, 50);
    else if (sr >= midpoint+2 && sr <= 30) mos(50, 200);
    else mos(9 * spr, 9 * spl);
  }
  digitalWrite(calout, LOW);
  counter = 7;
}
