void wall_cave() {
  motorSpeedB(255, 255);
  delay(50);
  digitalWrite(13, HIGH);
  digitalWrite(calout, LOW);
  int wall = 0;

  while (sum == 0) {
    sonar();
    check();
    //    debug();
    if (wall == 0) {
      if (sl != 0 && sl <= 8) motorSpeed(0, 150);
      else if (sl >= 10 && sl <= 30) motorSpeed(150, 0);
      else motorSpeed(150, 150);
      
      if (sr <= 10 && sr != 0) {
        m81 = m82 = millis();
        while (sr != 0 && sr <= 15) {
          motorSpeed(100, 100);
          m82 = millis();
          if (m82 - m81 >= 200) {
            wall = 1;
            break;
          }
        }
      }
    }

    else if (wall == 1) {
      if (sr != 0 && sr <= 8) motorSpeed(120, 0);
      else if (sr >=10 && sr <= 30) motorSpeed(0, 150);
      else motorSpeed(150, 150);
    }


  }
  digitalWrite(13, LOW);
  return;


}
