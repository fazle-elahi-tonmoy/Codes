void grab(byte a) {
  motor(30, 30);
  delay(100);
  lefthand.write(lservo[a]);
  righthand.write(rservo[a]);
  delay(250); counter++; reading();
  spl = sp - le;
  spr = sp - re;
  br = EEPROM.read(22);
  node = EEPROM.read(25);
}

void drop(bool a, bool b) {
  if(a == 0){
    motor(-250, -250); delay(br);
  }
  motor(0, 0);
  lefthand.write(lservo[0]);
  righthand.write(rservo[0]);
  delay(200);
  if(b==0) {
    motor(-80, 80); delay(turn * 5);
  }
  counter++; reading();
  cross = 0; flag = 0;
}

void servo_test() {
  byte cl = 3, b = 1, p = 8, sw, temp = 0;
  oled.set2X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      lefthand.write(lservo[cl]);
      righthand.write(rservo[cl]);
    }
    sw = rswitch();
    if (sw == 1 && temp < 2) temp++;
    else if (sw == 2) break;
    sw = lswitch();
    if (sw == 1 && temp > 0)  temp--;
    else if (sw == 2) {
      lefthand.write(lservo[0]);
      righthand.write(rservo[0]);
      break;
    }
  }
  intro();
}
