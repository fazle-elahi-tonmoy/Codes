void wall_follow() {
  digitalWrite(calout, HIGH);
  int flag = 0;
  int w_counter = 0;
  while (sum > 2) {
    sonar();
    check();
    if (((sf <= 50 && w_counter >= 3 ) || sf <= 13) && sf > 5) {
      motorSpeedB(6 * spr, 6 * spl);
      delay(90);
      digitalWrite(d90, HIGH);
      digitalWrite(d30, HIGH);
      (sl <= 30 && sl >= 5) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
      delay(430);
      (sl <= 30 && sl >= 5) ? motorSpeedL(6 * spr, 6 * spl) : motorSpeedR(6 * spr, 6 * spl);
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
      w_counter++;
      sonar();
      digitalWrite(d90, LOW);
      digitalWrite(d30, LOW);
    }

    else if (sl <= 11 && sl > 5) mos(0, 200);
    else if (sl >= 15 && sl <= 30) mos(200, 0);
    else if(sr <=11 && sr > 5) mos(200, 0);
    else if (sr >= 15 && sr <= 30) mos(0, 200);
    else mos(9 * spr, 9 * spl);
  }
  digitalWrite(calout, LOW);
  motorSpeedS();
  counter = 9;
}













void wall_function() {
  delay(500);
  digitalWrite(calout, HIGH);
  int flag = 0;
  int w_counter = 0;
  while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) {
    sonar();
    check();
    if (((sf <= 45 && w_counter >= 3 ) || sf <= 12) && sf > 5) {
      motorSpeedB(6 * spr, 6 * spl);
      delay(50);
      (sl <= 30 && sl >= 5) ? motorSpeedR(6 * spr, 6 * spl) : motorSpeedL(6 * spr, 6 * spl);
      delay(400);
      (sl <= 30 && sl >= 5) ? motorSpeedL(6 * spr, 6 * spl) : motorSpeedR(6 * spr, 6 * spl);
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
      w_counter++;
    }

    else if (sl > 5 && sl < 20 && sr > 5 && sr < 20) {
      if (sr - sl >= 4) mos(0, 150);
      else if (sl - sr >= 4) mos(150, 0);
      else mos(6 * spr, 6 * spl);
    }

    else mos(6 * spr, 6 * spl);
  }
  digitalWrite(calout, LOW);
  motorSpeedS();
}
