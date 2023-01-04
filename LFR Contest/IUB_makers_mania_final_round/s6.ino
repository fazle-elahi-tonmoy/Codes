else if (sum == 6) {

  m81 = m82 = millis();
  mov = 1;
  k30 = 0;
  k90 = 1;
  tcount = 1;
  if (counter == 1 || counter == 3) {
    mov = 0;
    k90 = 0;
  }
  while (sum == 5 || sum == 6 || sum == 4 || sum == 3 || sum == 2 || sum == 1) {
    digitalWrite(d30, HIGH);
    digitalWrite(d90, HIGH);
    check();
    m82 = millis();
    if (m82 - m81 >= 100) {
      if (sum == 6) {
        motorSpeedB(250, 250);
        delay(100);
        mov = 0;
        k30 = 0;
        k90 = 0;
        cross = 0;
        motorSpeedS();
        delay(3000);
      }
      else {
        if (counter == 2) {
          counter = 3;
          cross = 0;
        }
        else if (counter == 0 || counter == 5) cross = 1;
        else if (counter == 1) {
          cross = 2;
          tcount = 0;
        }
      }
      break;
    }
  }
  digitalWrite(d30, LOW);
  digitalWrite(d90, LOW);

  mi1 = millis();  //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.
}


mi2 = millis();
if ((mi2 - mi1 ) >= 500) {
  mov = 0;
  tcount = 0;
}//500ms por movement automatic 0 korar command


} // end of loop :)
