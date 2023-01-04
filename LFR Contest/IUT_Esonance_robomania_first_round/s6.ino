else if (sum == 6) {
  digitalWrite(d30, HIGH);
  digitalWrite(d90, HIGH);
  k30 = 0;
  mov = 1;
  k90 = 1;
  cross = 0;

  m81 = m82 = millis();
  while (sum == 5 || sum == 6 || sum == 4 || sum == 3 || sum == 2 || sum == 1) {
    check();
    m82 = millis();
    if (bin == 30 || bin == 45 || bin == 28 || bin == 14 || bin == 41 || bin == 37 )  {
      delay(100);
      mov = 1;
      k90 = 1;
      break;
    }
    else if (sl <= 15 && sl >= 7) break;
    else if (m82 - m81 >= 150) {
      if (sum == 6) {
        motorSpeedB(250, 250);
        delay(150);
        mov = 0;
        k30 = 0;
        k90 = 0;
        cross = 0;
        motorSpeedS();
        delay(3000);
        break;
      }
      else {
        if (tcount == 0) {
          cross = 2;
          tcount = 1;
          break;
        }
      }
    }

  }

  digitalWrite(d30, LOW);
  digitalWrite(d90, LOW);

  mi1 = millis();  //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.
}


mi2 = millis();
if (mi2 - mi1 >= 500) mov = 0;  //500ms por movement automatic 0 korar command

} // end of loop :)
