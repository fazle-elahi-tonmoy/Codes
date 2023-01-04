void automatic() {
  while (mode == 1) {
    if (Serial.available() > 0) {
      data =  Serial.read();
      if (data == 'X') mode = 0;
    }
    flame_follow();
  }
  stop_bot();
}

void flame_follow() {
  check();
  if (analogRead(5) == 1023 || bin == 0b11111) {
    backward();
    delay(100);
    stop_bot();
    while (bin != 0) {
      check();
      digitalWrite(relay, HIGH);
    }
    digitalWrite(relay, LOW);
  }
  else if (bin == 0) stop_bot();
//  else if (bin = 0b11100) {
//    th = 255;
//    right();
//    while (bin != 0b01110 && bin != 0b00100 && bin != 0b01100 && bin != 00110 && bin != 0) check();
//  }
//  else if (bin = 0b00111) {
//    th = 255;
//    left();
//    while (bin != 0b01110 && bin != 0b00100 && bin != 0b01100 && bin != 00110 && bin != 0) check();
//  }
  else if ((sensor[4] == 1 || sensor[3] == 1) && sensor[2] == 0) {
    th = 255;
    right();
    while (sensor [2] == 0 && bin != 0) check();
  }
  else if ((sensor[0] == 1 || sensor[1] == 1) && sensor[2] == 0) {
    th = 255;
    left();
    while (sensor[2] == 0 && bin != 0) check();
  }
  else {
    th = 80;
    forward();
  }
}

