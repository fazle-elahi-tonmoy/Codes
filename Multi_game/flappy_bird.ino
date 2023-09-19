void flappy_bird() {
  display.init();
  for (int i = 0; i < 4; i++) {
    zidx[i] = 128 + ((i + 1) * razmak);
    { prazan[i] = random(8, 32); }
  }

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  while (1) {
    display.clear();

    if (igra == 0) {
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 4, "Flappy ");
      display.drawXbm(0, 0, 128, 64, pozadina);
      display.drawXbm(20, 32, 14, 9, ptica);

      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 44, "press to start");
      if (digitalRead(button) == 0)
        igra = 1;
    }

    if (igra == 1) {
      display.setFont(ArialMT_Plain_10);
      display.drawString(3, 0, String(score));

      if (digitalRead(button) == 0) {
        if (stis == 0) {
          trenutno = millis();
          smjer = 1;
          sviraj = 1;
          stis = 1;
          ton = millis();
        }

      } else {
        stis = 0;
      }


      for (int j = 0; j < 4; j++) {
        display.setColor(WHITE);
        display.fillRect(zidx[j], 0, 6, 64);
        display.setColor(BLACK);
        display.fillRect(zidx[j], prazan[j], 6, sirinaProlaza);
      }

      display.setColor(WHITE);
      //  display.fillCircle(fx, fy, 4); // igrac
      display.drawXbm(fx, fy, 14, 9, ptica);

      for (int j = 0; j < 4; j++) {
        zidx[j] = zidx[j] - 0.01;
        if (zidx[j] < -7) {
          score = score + 1;


          digitalWrite(23, 1);
          prazan[j] = random(8, 32);

          zidx[j] = 128;
        }
      }
      if ((trenutno + 185) < millis())
        smjer = 0;

      if ((ton + 40) < millis())
        sviraj = 0;

      if (smjer == 0)
        fy = fy + 0.01;
      else
        fy = fy - 0.03;


      if (sviraj == 1)
        digitalWrite(23, 1);
      else
        digitalWrite(23, 0);

      if (fy > 63 || fy < 0) {
        igra = 0;
        fy = 22;
        score = 0;
        digitalWrite(23, 1);
        delay(500);
        digitalWrite(23, 0);
        for (int i = 0; i < 4; i++) {
          zidx[i] = 128 + ((i + 1) * razmak);
          { prazan[i] = random(4, 30); }
        }
      }

      for (int m = 0; m < 4; m++)
        if (zidx[m] <= fx + 7 && fx + 7 <= zidx[m] + 6) {


          if (fy < prazan[m] || fy + 8 > prazan[m] + sirinaProlaza) {
            igra = 0;
            fy = 22;
            score = 0;
            digitalWrite(23, 1);
            delay(500);
            digitalWrite(23, 0);
            for (int i = 0; i < 4; i++) {
              zidx[i] = 128 + ((i + 1) * razmak);
              { prazan[i] = random(8, 32); }
            }
          }
        }
      display.drawRect(0, 0, 128, 64);
    }

    display.display();
  }
}