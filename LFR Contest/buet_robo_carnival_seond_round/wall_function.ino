void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (sum==0) {
    sonar();
    check();
    if (sf <= 20 && sf >= 2) {
      //......................................................left turn
      if (sl <= 30 && sl >= 5) {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedR(6 * spr, 6 * spl);
        delay(450);
        motorSpeedL(6 * spr, 6 * spl);
        delay(50);
        while (flag = 0) {
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
        delay(450);
        motorSpeedR(6 * spr, 6 * spl);
        delay(50);
        while (flag = 0) {
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
    }
    else if (sl <= 18 && sl >= 5 && sr >= 22 && sr <= 30) mos(0, 150);
    else if (sr <= 18 && sr >= 5 && sl >= 22 && sl <= 30) mos(150, 0);
    else mos(6 * spr, 6 * spl);

  }
  digitalWrite(calout, LOW);
}













void wall_function() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    if (sf <= 20 && sf >= 2) {
      //......................................................left turn
      if (sl <= 30 && sl >= 5) {
        motorSpeedB(6 * spr, 6 * spl);
        delay(50);
        motorSpeedR(6 * spr, 6 * spl);
        delay(450);
        motorSpeedL(6 * spr, 6 * spl);
        delay(50);
        while (flag = 0) {
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
        delay(450);
        motorSpeedR(6 * spr, 6 * spl);
        delay(50);
        while (flag = 0) {
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
    }
    else if (sl <= 18 && sl >= 5 && sr >= 22 && sr <= 30) mos(0, 150);
    else if (sr <= 18 && sr >= 5 && sl >= 22 && sl <= 30) mos(150, 0);
    else mos(6 * spr, 6 * spl);
  }
  digitalWrite(calout, LOW);
  motorSpeedS();
}

