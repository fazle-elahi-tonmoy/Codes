void obstacle() {
  m2 = millis();
  if (m2 - m1 > 50) { //check the sonar value only after certain period of time (50ms)
    int sf = sonar.ping_cm();
    if (sf > 0 && sf < 15 && mode && digitalRead(sw)) {
      if (x == 'F' || x == 'G' || x == 'I') motor(0, 0); //if you were going forward, it will stop the robot
      digitalWrite(back_light, 1); //indicate that the robot has detected object
      while (sf > 0 && sf < 15 && mode && digitalRead(sw)) { //it will keep the robot in this loop as long as you detect obstacle infront of you
        sf = sonar.ping_cm(); delay(50); 
        if (bt.available()) {
          x = bt.read();
          if (x != 'F' && x != 'G' && x != 'I') {
            command(); break;
          }
          else if (x == 'S') command();
        }
      }
      digitalWrite(back_light, 0);
    }
    m1 = m2 = millis(); //refreshing the timer to check sonar value
  }
}
