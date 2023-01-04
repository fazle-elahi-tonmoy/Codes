void wall_follow() {
  digitalWrite(calout, HIGH);
  spl = 25;
  spr = 22;
  int flag = 0;
  int turn = 0;
  int fdelay = 300;
  int tdelay = 450;
  while (sum==0) {
    sonar();
    check();
    if (sf <= 13 && sf >= 2) {
      //......................................................left turn
      if (sl <= 30 && sl >= 5) {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedR(6 * spr, 6 * spl);
        delay(tdelay);
        motorSpeedL(6 * spr, 6 * spl);
        delay(50);
        while (flag == 0) {
          sonar();
          mos(6 * spr, 6 * spl);
          if (sr <= 30 && sr >= 5) {
            m82 = m81 = millis();
            while (sr <= 30 && sr >= 5) {
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
      }
      else {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedL(6 * spr, 6 * spl);
        delay(tdelay);
        motorSpeedR(6 * spr, 6 * spl);
        delay(50);
        while (flag == 0) {
          sonar();
          mos(6 * spr, 6 * spl);
          if (sl <= 30 && sl >= 5) {
            m82 = m81 = millis();
            while (sl <= 30 && sl >= 5) {
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
      }
      turn++;
    }
    else if (sl <= 12 && sl >= 0 && sr >= 16 && sr <= 40) mos(0, 150);
    else if (sr <= 12 && sr >= 0 && sl >= 16 && sl <= 40) mos(150, 0);
    else mos(6 * spr, 6 * spl);
  }
  digitalWrite(calout, LOW);
  spl = 18;
  spr = 15;
}





void wall_function() {
  digitalWrite(calout, HIGH);
  spl = 25;
  spr = 22;
  int flag = 0;
  int turn = 0;
  int fdelay = 300;
  int tdelay = 450;
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    if (sf <= 13 && sf >= 2) {
      //......................................................left turn
      if (sl <= 30 && sl >= 5) {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedR(6 * spr, 6 * spl);
        delay(tdelay);
        motorSpeedL(6 * spr, 6 * spl);
        delay(50);
        while (flag == 0) {
          sonar();
          mos(6 * spr, 6 * spl);
          if (sr <= 30 && sr >= 5) {
            m82 = m81 = millis();
            while (sr <= 30 && sr >= 5) {
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
      }
      else {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedL(6 * spr, 6 * spl);
        delay(tdelay);
        motorSpeedR(6 * spr, 6 * spl);
        delay(50);
        while (flag == 0) {
          sonar();
          mos(6 * spr, 6 * spl);
          if (sl <= 30 && sl >= 5) {
            m82 = m81 = millis();
            while (sl <= 30 && sl >= 5) {
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
      }
      turn++;
    }
    else if (sl <= 12 && sl >= 0 && sr >= 16 && sr <= 40) mos(0, 150);
    else if (sr <= 12 && sr >= 0 && sl >= 16 && sl <= 40) mos(150, 0);
    else mos(6 * spr, 6 * spl);
  }
  digitalWrite(calout, LOW);
  spl = 18;
  spr = 15;
}
