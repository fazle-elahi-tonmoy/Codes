else if (sum == 3) {
  if (bin == 11 || bin == 13 || bin == 9 || bin == 25 ) {
    k30 = 1;
    mov = 1;
    if (counter == 1 && (sl>20 || sl<=6)) {
      mos(10 * spr, 10 * spl);
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 150) {
          special_logic();
          break;
        }
      }
    }
  }

  else if ( bin == 52 || bin == 44 || bin == 36 || bin == 38) {
    k30 = 2;
    mov = 2;
  }

  else if (bin == 7) {
    k90 = 1;
    mov = 1;
    m81 = m82 = millis();
    while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
      check();
      m82 = millis();
      if (bin == 30 || bin == 45 || bin == 28 || bin == 14 || bin == 41 || bin == 37 )  {
        delay(100);
        mov = 1;
        k90 = 1;
        break;
      }
      if (m82 - m81 >= 120) {
        cross = 1;
        break;
      }
    }
  }

  else if (bin == 56) {
    mov = 2;
    k90 = 2;
  }

  else if (bin == 35 || bin == 49) y_section();

  mi1 = millis();   //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.

}// end of logic
