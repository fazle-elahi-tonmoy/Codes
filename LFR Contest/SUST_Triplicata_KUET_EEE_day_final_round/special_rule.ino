void special_LHR() {
  braking_mechanism(1);
  motorSpeedL(5*spl, 5*spr);
  for(int i = 0; i<=200; i++){
    delay(1);
    check();
  }
  motorSpeedR(5*spl, 5*spr);
  while (sensor[2] == 0 && sensor [3] == 0) check();
  motorSpeedL(5*spl, 5*spr);
  delay(br);
  mos(10 * spl, 10 * spr);
  counter ++;
}

void special_RHR() {
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
