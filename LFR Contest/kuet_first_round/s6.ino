else if (sum == 6) {

  m81 = m82 = millis();
  while (sum == 5 || sum == 6 || sum == 4 || sum == 3) {
    digitalWrite(d30, HIGH);
    digitalWrite(d90, HIGH);
    mov = 1;
    k30 = 0;
    k90 = 1;
    check();
    m82 = millis();
    if (m82 - m81 >= 150) {
      motorSpeedB(200, 200);
      delay(100);
      mov = 0;
      k30 = 0;
      k90 = 0;
      cross = 0;
      motorSpeedS();
      delay(2000);
      break;
    }

  }

  digitalWrite(d30, LOW);
  digitalWrite(d90, LOW);

  mi1 = millis();  //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.
}


mi2 = millis();
if (mi2 - mi1 >= 500) mov = 0;  //500ms por movement automatic 0 korar command


} // end of loop :)




