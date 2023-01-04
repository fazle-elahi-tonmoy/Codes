else if (sum == 6) {

  m81 = m82 = millis();
  while (sum == 5 || sum == 6 || sum == 4 || sum == 3 || sum == 2 || sum == 1) {
    digitalWrite(d30, HIGH);
    digitalWrite(d90, HIGH);
    mov = 1;
    k30 = 0;
    k90 = 1;
    check();
    m82 = millis();
    if (m82 - m81 >= 120) {
      if (sum == 6) {
        if (counter1 == 0) {
          while (sum != 2 && sum != 1) {
            check();
            mos(10 * spr, 10 * spl);
          }
          counter1 = 1;
          EEPROM.write(10, 1);
          break;
        }
        else {
          motorSpeedB(250, 250);
          delay(100);
          mov = 0;
          k30 = 0;
          k90 = 0;
          cross = 0;
          motorSpeedS();
          delay(3000);
          counter1 = 0;
          EEPROM.write(10, 0);
          break;
        }
      }

      else {
        digitalWrite(13,HIGH);
        if (counter2 == 0) {
          counter2 = 1;
          break;
        }
        else {
          cross = 1;
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
if ((mi2 - mi1 )>= 500) mov = 0;  //500ms por movement automatic 0 korar command


} // end of loop :)
