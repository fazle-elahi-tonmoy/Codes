void line_follow() {
  oled.clear(); oled.set2X(); text("LineFollow",04,3); delay(500);
   while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) { //infinite loop
    reading();
    if (sum == 0) {
      if (flag != 's') {
//        motor(10 * spl, 10 * spr); delay(30); //time given to move robot forward for a certain time to adjust in 90 degree line
        if (flag == 'l') {
          motor(-6 * spl, 6 * spr);
          //          while(sensor != 0b001100 && sensor != 0b001000 && sensor != 0b000100) reading();
          while (s[2] == 0 && s[3] == 0) reading();
        }
        else if (flag == 'r') {
          motor(6 * spl, -6 * spr);
          while (s[2] == 0 && s[3] == 0) reading();
        }
        else if (flag == 't') {
          motor(6 * spl, -6 * spr);
          while (s[2] == 0 && s[3] == 0) reading();
        }
        flag = 's'; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (sensor == 0b001100) {
        if (flag == 't') flag = 's';
        if (pos != 0) {
          (pos == 1) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          delay(10); pos = 0;  //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr);
      }
      //right side portion
      else if (sensor == 0b000100) {
        if (flag == 't') flag = 's';
        motor(10 * spl, 9 * spr);
      }
      else if (sensor == 0b000110) {
        pos = 1; motor(10 * spl, 7 * spr);
      }
      else if (sensor == 0b000010) {
        pos = 1; motor(10 * spl, 5 * spr);
      }
      else if (sensor == 0b000011) {
        pos = 1; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000001) {
        pos = 1;
        motor(10 * spl, 0 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) {
        if (flag == 't') flag = 's';
        motor(9 * spl, 10 * spr);
      }
      else if (sensor == 0b011000) {
        pos = -1; motor(7 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        pos = -1; motor(5 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        pos = -1; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        pos = -1; motor(0 * spl, 10 * spr);
      }
    }

    else if ((sum == 3 || sum == 4 || sum == 5) && flag != 't') { //only for sharp turn logic
      if (sensor == 0b101100 || sensor == 0b100110 || sensor == 0b110100) flag = 'l';
      else if (sensor == 0b001101 || sensor == 0b011001 || sensor == 0b001011) flag = 'r';
      else if (sensor == 0b111100 || sensor == 0b111000 || sensor == 0b111110) flag = 'l';
      else if (sensor == 0b001111 || sensor == 0b000111 || sensor == 0b011111) flag = 'r';
    }

    else if (sum == 6) {
      flag = 't';
      delay(100);
      reading();
      if (sum == 6) { //stop point detection
        motor(0, 0);
        while (sum == 6 && digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) reading();
        if(digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) delay(1000);
      }
    }
  }
  intro();  motor(0, 0); digitalWrite(light, 0); 
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}
