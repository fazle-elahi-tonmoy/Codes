void wall_obstacle() {
  //prothome brake
  motorSpeedB(200, 200);
  delay(100);
  spr = 24;
  spl = 25;
  digitalWrite(calout, HIGH);
  digitalWrite(13, HIGH);
  sonar();

  //tarpor daane ghurate hobe jotokhon nabot er nak ta obstacle theke dure sore jay
  int obstacle=0;
  while (sf < 50) {
    sonar();
    motorSpeedR(4 * spr, 4 * spl);
    m81 = m82 = millis();
    while(sf==0){
      sonar();
       m82 = millis();
       if (m82 - m81 >= 100) {
          obstacle=1;
          break;
       }
    }
    if(obstacle==1) break;
  }
  if(obstacle==0) delay(100);
  motorSpeedL(6 * spr, 6 * spl);
  delay(50);
  
  //erpor kichukkhon kunakuni vabe samne agate hobe
  mos(6 * spr, 6 * spl);
  delay(500);
  motorSpeedB(150, 150);
  delay(100);

  //erpor bot ta soja korte hobe. mane obstacle er sathe parallel korte hobe.
  sonar();
  while (sl >= 15 || sl == 0) {
    sonar();
    mos(150, -100);
  }

  //erpor soja jaite hobe jotokkhon na obstacle ta par na hoy
  sonar();
  obstacle=0;
  while (sl <= 50) {
    sonar();
    mos(6 * spr, 6 * spl);
    m81 = m82 = millis();
    while(sl<=5){
      sonar();
       m82 = millis();
       if (m82 - m81 >= 150) {
          obstacle=1;
          break;
       }
    }
    if(obstacle==1) break;
  }
  if(obstacle==0) delay(150);
  motorSpeedB(150, 150);
  delay(100);

  //erpor ektu ghure kunakuni position e nite hobe jaate kore soja gele line pay
  mos(150, 0);
  delay(450);

  //jotokkhon na majhkhaner duita black pabe totokkhon soja jaite thakbe.
  check();
  while (sensor[1] == 0 ) {
    check();
    mos(6 * spr, 6 * spl);
  }
  k=5;

digitalWrite(13, LOW);
digitalWrite(calout, LOW);
}//shesh!!!!

