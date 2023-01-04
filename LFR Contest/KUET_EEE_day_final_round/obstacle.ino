void wall_obstacle() {
  //prothome brake
  braking_mechanism();
  digitalWrite(calout, HIGH);
  digitalWrite(13, HIGH);
  sonar();

  //tarpor daane ghurate hobe jotokhon nabot er nak ta obstacle theke dure sore jay
  int obstacle = 0;
  while (sf < 50) {
    sonar();
    motorSpeedL(4 * spr, 4 * spl);
    m81 = m82 = millis();
    while (sf == 0 || sf > 50) {
      sonar();
      m82 = millis();
      if (m82 - m81 >= 150) {
        obstacle = 1;
        break;
      }
    }
    if (obstacle == 1) break;
  }
  if (obstacle == 0) delay(100);
  motorSpeedR(6 * spr, 6 * spl);
  delay(50);

  //erpor kichukkhon kunakuni vabe samne agate hobe
  mos(6 * spr, 6 * spl);
  delay(700);
  motorSpeedB(150, 150);
  delay(100);

  //erpor bot ta soja korte hobe. mane obstacle er sathe parallel korte hobe.
  sonar();
  while (sr >=21 || sr<=7 ) {
    sonar();
    mos(0, 150);
  }

  //erpor soja jaite hobe jotokkhon na obstacle ta par na hoy
  sonar();
  obstacle = 0;
  while (sr <= 50) {
    sonar();
    mos(6 * spr, 6 * spl);
    m81 = m82 = millis();
    while (sr <= 5) {
      sonar();
      m82 = millis();
      if (m82 - m81 >= 50) {
        obstacle = 1;
        break;
      }
    }
    if (obstacle == 1) break;
  }
  if (obstacle == 0) delay(150);
  motorSpeedB(150, 150);
  delay(100);

  //erpor ektu ghure kunakuni position e nite hobe jaate kore soja gele line pay
  mos(-150, 150);
  delay(250);

  //jotokkhon na majhkhaner duita black pabe totokkhon soja jaite thakbe.
  check();
  mos(6 * spr, 6 * spl);
  while (sum == 0) check();
  while (sum  > 0) check();
  delay(btd);
  motorSpeedL(6 * spr, 6 * spl);
  while (sensor[2] == 0 && sensor[3] == 0) check();
  motorSpeedR(6 * spr, 6 * spl);
  delay(br);
  k = 0;

  digitalWrite(13, LOW);
  digitalWrite(calout, LOW);
  counter = 8;
}//shesh!!!!
