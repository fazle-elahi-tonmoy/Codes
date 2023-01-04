else if (sum == 3) {
  if (bin == 11 || bin == 13 || bin == 9) {
    k30 = 1;
    mov = 1;
    if (side == 1 && counter == 0) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 250) {
          special_logic();
          break;
        }
      }
    }
  }

  else if ( bin == 52 || bin == 44 || bin == 36) {
    k30 = 2;
    mov = 2;
    if (side == 2 && counter == 0) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 250) {
          special_logic();
          break;
        }
      }
    }
  }

  else if (bin == 7) {
    k90 = 1;
    mov = 1;
    if (side == 1) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 120) {
          cross = 1;
          break;
        }
      }
    }
  }

  else if (bin == 56) {
    mov = 2;
    k90 = 2;
    if (side == 2) {
      m81 = m82 = millis();
      while (sum == 4 || sum == 3 || sum == 1 || sum == 2) {
        check();
        m82 = millis();
        if (m82 - m81 >= 120) {
          cross = 2;
          break;
        }
      }
    }
  }

  //  else if (bin == 14 && mov == 0) {
  //    k30 = 1;
  //    mov = 1;
  //    if (side == 1) {
  //      m81 = m82 = millis();
  //      while (sum == 3 || sum == 1 || sum == 2) {
  //        check();
  //        m82 = millis();
  //        if (m82 - m81 >= 150) {
  //          special_logic();
  //          break;
  //        }
  //      }
  //    }
  //  }
  //
  //  else if (bin == 28 && mov == 0) {
  //    k30 = 2;
  //    mov = 2;
  //    if (side == 2) {
  //      m81 = m82 = millis();
  //      while (sum == 3 || sum == 1 || sum == 2) {
  //        check();
  //        m82 = millis();
  //        if (m82 - m81 >= 150) {
  //          special_logic();
  //          break;
  //        }
  //      }
  //    }
  //  }

  else if ((bin == 35 || bin == 49) && counter == 1) y_section();

  mi1 = millis();   //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.

}// end of logic
