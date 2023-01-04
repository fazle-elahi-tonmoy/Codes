void special_logic() {
  if (side == 1) {
    digitalWrite(d30, HIGH);
    motorSpeedB(200, 200);;
    delay(brake);
    motorSpeedS();
    delay(200);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedR(6 * spr, 6 * spl);
    }
    while (sensor[1]==0) {
      check();
      motorSpeedR(6 * spr, 6 * spl);

    }
    motorSpeedL(6 * spr, 6 * spl);
    delay(5 * dt);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    k = 0;
    digitalWrite(d30, LOW);
  }

  else if (side == 2) {
    digitalWrite(d30, HIGH);
    motorSpeedB(200, 200);;
    delay(brake);
    motorSpeedS();
    delay(200);

    while (sensor[2] == 1 || sensor[3] == 1) {
      check();
      motorSpeedL(6 * spr, 6 * spl);

    }
    while (sensor[4]==0) {
      check();
      motorSpeedL(6 * spr, 6 * spl);

    }
    motorSpeedR(6 * spr, 6 * spl);
    delay(5 * dt);
    k90 = 0;
    mov = 0;
    cl = base;
    brake = cl / d;
    k = 0;
    digitalWrite(d30, LOW);
  }
}
