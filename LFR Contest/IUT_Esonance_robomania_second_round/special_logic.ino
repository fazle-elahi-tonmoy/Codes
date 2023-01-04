void special_logic(){
  digitalWrite(d90, HIGH);
    motorSpeedB(10 * spr, 10 * spl);
    brake = cl / d;
    delay(brake * 2);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedR(6 * spr, 6 * spl);

    }
    while (sensor[1]==0) {
      check();
      motorSpeedR(6 * spr, 6 * spl);

    }
    motorSpeedL(6 * spr, 6 * spl);
    delay(br);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    k = 0;
    digitalWrite(d90, LOW);
}
