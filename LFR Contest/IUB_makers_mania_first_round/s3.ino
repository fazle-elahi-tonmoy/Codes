else if (sum == 3) {
  if (bin == 11 || bin == 13  ) {
    k30 = 1;
    mov = 1;
  }

  else if ( bin == 52 || bin == 44  ) {
    k30 = 2;
    mov = 2;
  }

  else if (bin == 7) {
    k90 = 1;
    mov = 1;
    if (counter1 >= 1) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 100) {
          cross = 1;
          break;
        }
      }
    }

  }

  else if (bin == 56) {
    mov = 2;
    k90 = 2;
    if (counter1 == 1) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 100) {
          cross = 2;
          counter1++;
          break;
        }
      }
    }
  }

  mi1 = millis();   //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.

}// end of logic
