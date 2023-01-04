else if (sum == 4 || sum == 5) {
  if (  bin == 15 || bin == 31) {    //31 mane 011111
    k90 = 1;
    mov = 1;
    m81 = m82 = millis();
    while (sum == 5 || sum == 4 || sum == 3 || sum == 1 || sum == 2) {
      check();
      m82 = millis();
      if (bin == 30 || bin == 45 || bin == 28 || bin == 14 || bin == 41 || bin == 37 )  {
        delay(100);
        mov = 1;
        k90 = 1;
        break;
      }
      else if (m82 - m81 >= 120) {
        cross = 1;
        break;
      }
    }
  }

  else if (  bin == 60 || bin == 62) {   //62 mane 111110
    k90 = 2;
    mov = 2;
  }

  else if (bin == 51 || bin == 39 || bin == 57) y_section();

  mi1 = millis ();      //eta dile 500ms por automatic movement 0 hoye jabe. er moddhe faka line paile turn nibe.

}
