void special_LHR() {
  braking_mechanism();
  motorSpeedL(6 * spr, 6 * spl);
  for(int i = 1; i<=LHR1; i++){
    delay(1);
    check();
  }
  motorSpeedR(6 * spr, 6 * spl);
  while (sensor[2] == 0 && sensor [3] == 0) check();
  motorSpeedL(6 * spr, 6 * spl);
  delay(br);
  mos(10 * spr, 10 * spl);
  counter ++;
}

void special_RHR() {
  braking_mechanism();
  motorSpeedR(6 * spr, 6 * spl);
  for(int i = 0; i<=RHR2; i++){
    delay(1);
    check();
  }
  motorSpeedL(6 * spr, 6 * spl);
  while (sensor[2] == 0 && sensor [3] == 0) check();
  motorSpeedR(6 * spr, 6 * spl);
  delay(br);
  mos(10 * spr, 10 * spl);
  counter ++;
}
