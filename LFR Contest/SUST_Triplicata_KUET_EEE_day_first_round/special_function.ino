void special_RHR1() {
  braking_mechanism(1);
  motorSpeedR(5*spl, 5*spr);
  for(int i = 0; i<=150; i++){
    delay(1);
    check();
  }
  while (sensor[2] == 0 && sensor [3] == 0) check();
  motorSpeedL(5*spl, 5*spr);
  delay(br);
  mos(10 * spl, 10 * spr);
  counter ++;
}

void special_RHR2() {
  braking_mechanism(1);
  motorSpeedR(5*spl, 5*spr);
  for(int i = 0; i<=200; i++){
    delay(1);
    check();
  }
  motorSpeedL(5*spl, 5*spr);
  while (sensor[2] == 0 && sensor [3] == 0) check();
  motorSpeedR(5*spl, 5*spr);
  delay(br);
  mos(10 * spl, 10 * spr);
  counter ++;
}
