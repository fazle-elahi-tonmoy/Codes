void wall_obstacle() {
  //prothome brake
  motorSpeedB(200, 200);
  delay(100);
  spr = 22;
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

  //jotokkhon na majhkhaner duita black pabe totokkhon soja jaite thakbe.
  check();
  while (sensor[1] == 0) {
    check();
    mos(6 * spr, 6 * spl);
  }
  k=5;

digitalWrite(13, LOW);
digitalWrite(calout, LOW);
}//shesh!!!!
