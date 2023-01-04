void manual() {
  while (mode == 0) {
    if (Serial.available() > 0) {
      data =  Serial.read();
      Serial.print(data);
      Serial.print("\n");
      if (data == 'F')      forward();
      else if (data == 'B') backward();
      else if (data == 'L') left();
      else if (data == 'R') right();
      else if (data == 'G') forward_left();
      else if (data == 'I') forward_right();
      else if (data == 'H') backward_left();
      else if (data == 'J') backward_right();
      else if (data == 'S') stop_bot();
      else if (data == 'W') digitalWrite(relay, HIGH);
      else if (data == 'w') digitalWrite(relay, LOW);
      else if (data == '0') th = 60;
      else if (data == '1') th = 80;
      else if (data == '2') th = 100;
      else if (data == '3') th = 120;
      else if (data == '4') th = 140;
      else if (data == '5') th = 160;
      else if (data == '6') th = 180;
      else if (data == '7') th = 200;
      else if (data == '8') th = 225;
      else if (data == '9') th = 255;
      else if (data == 'q') th = 255;
      //      else if (data == 'x') {
      //        stop_bot();
      //        mode=1;
      //      }
      //      else stop_bot();
    }
  }
}
