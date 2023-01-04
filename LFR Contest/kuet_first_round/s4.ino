else if (sum == 4 || sum == 5) {
  if (  bin == 15 || bin == 31) {    //31 mane 011111
    k90 = 1;
    mov = 1;
    m81 = m82 = millis();
    while (sum == 5 || sum == 4 || sum == 3 || sum == 1 || sum == 2) {
      check();
      m82 = millis();
      if (m82 - m81 >= 150) {
        cross = 1;
        break;
      }
    }
  }

  else if (  bin == 60 || bin == 62) {   //62 mane 111110
    k90 = 2;
    mov = 2;
  }

  mi1 = millis ();      //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.

}

