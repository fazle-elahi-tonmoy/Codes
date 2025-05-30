void lfr() {
  reading();
  sonar_read();
  if (sum == 0) (flag == 'r') ? motor(250, -100) : motor(-100, 250);
  if (s[0]) flag = 'r';
  if (s[5]) flag = 'l';
  PID = kp * error;
  int motorL = baseL + PID;
  int motorR = baseR - PID;
  (distance > 10) ? motor(motorL, motorR) : motor(0, 0);
  if ((ss[0] || ss[1]) && millis() - obs_timer > 2000) {
    if (count >= 2) {
      order = 0;
      count = 0;
      motor(0, 0);
      return;
    }
    mySerial.println("Table Detected!");
    if (table[count] == 1) {
      motor(0, 0);
      delay(1000);
      (ss[1]) ? servo.write(0) : servo.write(180);
      delay(5000);
      servo.write(90);
      delay(1000);
      table[count] = 0;
      mySerial.println("Order Delivered!");
    }
    count++;
    obs_timer = millis();
  }
}