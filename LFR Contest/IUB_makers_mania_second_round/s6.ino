else if (sum == 6) {
  digitalWrite(d30, HIGH);
  digitalWrite(d90, HIGH);
  k30 = 0;
  cross = 0;
  if (side == 1) {
    mov = 1;
    k90 = 1;
  }
  else {
    mov = 2;
    k90 = 2;
  }

  m81 = m82 = millis();
  while (sum == 5 || sum == 6 || sum == 4 || sum == 3) {
    check();
    m82 = millis();
    if (m82 - m81 >= 150) {
      if (counter == 0) {
        counter_logic();
        break;
      }
      else {
        motorSpeedB(250, 250);
        delay(150);
        mov = 0;
        k30 = 0;
        k90 = 0;
        cross = 0;
        motorSpeedS();
        delay(3000);
        counter = 0;
        EEPROM.write(10, 0);
        break;
      }
    }

  }

  digitalWrite(d30, LOW);
  digitalWrite(d90, LOW);

  mi1 = millis();  //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.
}


mi2 = millis();
if (mi2 - mi1 >= 200) mov = 0;  //500ms por movement automatic 0 korar command


} // end of loop :)
