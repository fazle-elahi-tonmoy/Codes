void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  int turn = 0;
  int fdelay = 300;
  int tdelay = 450;
  while (sum == 0) {
    sonar();
    check();
    if (sf <= 20 && sf >= 2) {
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
    else if (sl <= 18 && sl >= 0 && sr >= 22 && sr <= 50) mos(0, 150);
    else if (sr <= 18 && sr >= 0 && sl >= 22 && sl <= 50) mos(150, 0);
    else mos(6 * spr, 6 * spl);

    m81 = m82 = millis();
    while ((sl <= 5 || sl > 50) && sr >= 0 && sr <= 50 && (turn >= 3 || counter == 1)) {
      m82 = millis();
      digitalWrite(d90, HIGH);
      digitalWrite(d30, HIGH);
      sonar();
      if (m82 - m81 >= fdelay || (sf>=5 && sf<=76)) {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedL(6 * spr, 6 * spl);
        delay(tdelay);
        motorSpeedR(6 * spr, 6 * spl);
        delay(50);
        while (flag == 0) {
          sonar();
          mos(6 * spr, 6 * spl);
          int t = 0;
          while (sl <= 30 && sl >= 5) {
            sonar();
            delay(1);
            t++;
            if (t >= 100) {
              flag = 1;
              break;
            }
          }
        }
        flag = 0;
        break;
      }
    }
    digitalWrite(d90, LOW);
    digitalWrite(d30, LOW);




  }
  digitalWrite(calout, LOW);
}














void wall_function() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  int turn = 0;
  int fdelay = 300;
  int tdelay = 450;
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    if ((sf <= 20 && sf >= 2 && (turn<3)) || (sf <=76 && sf>2 && (turn>=3 || counter ==1))) {
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
    else if (sl <= 18 && sl >= 0 && sr >= 22 && sr <= 50) mos(0, 150);
    else if (sr <= 18 && sr >= 0 && sl >= 22 && sl <= 50) mos(150, 0);
    else mos(6 * spr, 6 * spl);
    
  }
  digitalWrite(calout, LOW);
}
