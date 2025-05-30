int metx = 0;
int mety = 0;
int postoji = 0;
int nep = 8;
int smjer = 0;
int go = 0;
int rx1 = 95;
int ry1 = 0;
int rx2 = 95;
int ry2 = 0;
int rx3 = 95;
int ry3 = 0;
int bodovi = 0;

int brzina = 1;  //speed of bullet
int bkugle = 1;
int najmanja = 600;
int najveca = 1200;
int promjer = 10;

int rx4 = 95;
int ry4 = 0;
int zivoti = 5;
int poc = 0;
int ispaljeno = 0;
int nivo = 1;
int centar = 95;
unsigned long pocetno = 0;
unsigned long odabrano = 0;
unsigned long trenutno = 0;
unsigned long nivovrije = 0;
int poz = 30;

void space_game() {
  space_war_stating_screen();
  nivovrije = millis();
  uint32_t time_spent = millis();
  while (1) {
    if (push(l1))
      if (game_pause()) return;
      else {
        int temp1 = trenutno - nivovrije;
        int temp2 = trenutno - time_spent;
        trenutno = millis();
        nivovrije = trenutno - temp1;
        time_spent = trenutno - temp2;
      }
    if (!go) {
      display.clearDisplay();
      draw_stars();

      if (poc == 0) {
        pocetno = millis();
        odabrano = random(400, 1200);
        poc = 1;
      }
      trenutno = millis();
      if ((trenutno - nivovrije) > 60000) {
        nivovrije = trenutno;
        nivo = nivo + 1;

        brzina = brzina + 1;  //brizna neprijateljevog metka
        if (nivo % 2 == 0) {
          bkugle = bkugle + 1;
          promjer = promjer - 1;
        }
        najmanja = najmanja - 50;
        najveca = najveca - 50;
      }



      if ((odabrano + pocetno) < trenutno) {
        poc = 0;
        ispaljeno = ispaljeno + 1;
        if (ispaljeno == 1) {
          rx1 = 95;
          ry1 = nep;
        }
        if (ispaljeno == 2) {
          rx2 = 95;
          ry2 = nep;
        }
        if (ispaljeno == 3) {
          rx3 = 95;
          ry3 = nep;
        }


        if (ispaljeno == 4) {
          rx4 = 95;
          ry4 = nep;
        }
      }


      if (ispaljeno > 0) {
        display.drawCircle(rx1, ry1, 2, 1);
        rx1 = rx1 - brzina;
      }

      if (ispaljeno > 1) {
        display.drawCircle(rx2, ry2, 1, 1);
        rx2 = rx2 - brzina;
      }

      if (ispaljeno > 2) {
        display.drawCircle(rx3, ry3, 4, 1);
        rx3 = rx3 - brzina;
      }

      if (ispaljeno > 3) {
        display.drawCircle(rx4, ry4, 2, 1);
        rx4 = rx4 - brzina;
      }


      input_read();
      if (joystick[1] == 1 && poz >= 2) {
        poz = poz - 2;
      }

      if (joystick[1] == -1 && poz <= 46) {
        poz = poz + 2;
      }

      if (digitalRead(r1) == 0 && postoji == 0) {
        postoji = 1;
        metx = 6;
        mety = poz + 8;
        tone(buzzer, 1200, 20);
      }
      if (postoji == 1) {
        metx = metx + 8;
        display.drawLine(metx, mety, metx + 4, mety, 1);
      }

      display.drawBitmap(4, poz, dioda16, 16, 16, 1);
      display.fillCircle(centar, nep, promjer, 1);
      display.fillCircle(centar + 2, nep + 3, promjer / 3, 0);

      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(33, 57);
      display.println("score:");
      display.setCursor(68, 57);
      display.println(bodovi);

      display.setCursor(33, 0);
      display.println("lives:");
      display.setCursor(68, 0);
      display.println(zivoti);

      display.setCursor(110, 0);
      display.println("L:");

      display.setCursor(122, 0);
      display.println(nivo);

      display.setCursor(108, 57);
      display.println((trenutno - time_spent) / 1000);
      display.display();

      if (metx > 128) postoji = 0;



      if (smjer == 0) {
        nep = nep + bkugle;
      } else {
        nep = nep - bkugle;
      }

      if (nep >= (64 - promjer))
        smjer = 1;
      if (nep <= promjer)
        smjer = 0;

      if (mety >= nep - promjer && mety <= nep + promjer)
        if (metx > (centar - promjer) && metx < (centar + promjer)) {
          metx = -20;
          tone(buzzer, 500, 20);
          bodovi = bodovi + 1;
          postoji = 0;
        }

      int pozicija = poz + 8;
      if (ry1 >= pozicija - 8 && ry1 <= pozicija + 8)
        if (rx1 < 12 && rx1 > 4) {
          rx1 = 95;
          ry1 = -50;
          tone(buzzer, 100, 100);
          zivoti = zivoti - 1;
        }

      if (ry2 >= pozicija - 8 && ry2 <= pozicija + 8)
        if (rx2 < 12 && rx2 > 4) {
          rx2 = -50;
          ry2 = -50;
          tone(buzzer, 100, 100);
          zivoti = zivoti - 1;
        }

      if (ry3 >= pozicija - 8 && ry3 <= pozicija + 8)
        if (rx3 < 12 && rx3 > 4) {
          rx3 = -50;
          ry3 = -50;
          tone(buzzer, 100, 100);
          zivoti = zivoti - 1;
        }

      if (ry4 >= pozicija - 8 && ry4 <= pozicija + 8)
        if (rx4 < 12 && rx4 > 4) {
          rx4 = 200;
          ry4 = -50;
          ispaljeno = 0;
          tone(buzzer, 100, 100);
          zivoti = zivoti - 1;
        }

      if (rx4 < 1) {
        ispaljeno = 0;
        rx4 = 200;
      }

      if (zivoti == 0)
        go = 1;
    }

    else {
      if (zivoti == 0) zivoti = 5;
      bool over_state = game_over(bodovi);
      if (over_state) return;
      else ponovo();
    }
  }
}

void space_war_stating_screen() {
  display.clearDisplay();
  display.setTextSize(0);
  display.drawBitmap(6, 11, storm, 48, 48, 1);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(65, 14);
  display.println("xWing");
  display.setFont();
  display.setCursor(65, 17);
  display.setTextSize(0);
  display.println("vs");
  display.setCursor(0, 0);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(65, 39);
  display.println("Death");
  display.setFont();
  display.setCursor(65, 42);
  display.println("star ");
  display.setTextSize(0);
  display.setCursor(55, 55);
  display.println("by TechTopia");
  display.setCursor(65, 20);
  display.display();
  display.setFont();
  while (digitalRead(r1))
    for (int thisNote = 0; thisNote < sizeof(star_wars_melody) / sizeof(int); thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(buzzer, star_wars_melody[thisNote], noteDuration);
      delay(noteDuration);
      if (!digitalRead(r1)) break;
    }
}

void draw_stars() {

  display.drawPixel(50, 30, 1);
  display.drawPixel(30, 17, 1);
  display.drawPixel(60, 18, 1);
  display.drawPixel(55, 16, 1);
  display.drawPixel(25, 43, 1);
  display.drawPixel(100, 43, 1);
  display.drawPixel(117, 52, 1);
  display.drawPixel(14, 49, 1);
  display.drawPixel(24, 24, 1);
  display.drawPixel(78, 36, 1);
  display.drawPixel(80, 57, 1);
  display.drawPixel(107, 11, 1);
  display.drawPixel(150, 11, 1);
  display.drawPixel(5, 5, 1);
  display.drawPixel(8, 7, 1);
  display.drawPixel(70, 12, 1);
  display.drawPixel(10, 56, 1);
  display.drawPixel(70, 25, 1);
}


void ponovo() {
  metx = 0;
  mety = 0;
  postoji = 0;
  nep = 8;
  smjer = 0;
  go = 0;
  rx1 = 95;
  ry1 = 0;
  rx2 = 95;
  ry2 = 0;
  rx3 = 95;
  ry3 = 0;
  bodovi = 0;

  brzina = 1;  //the speed of the enemy's bullet
  bkugle = 1;
  najmanja = 600;
  najveca = 1200;
  promjer = 12;

  rx4 = 95;
  ry4 = 0;
  zivoti = 5;
  poc = 0;
  ispaljeno = 0;
  nivo = 1;
  pocetno = 0;
  odabrano = 0;
  trenutno = 0;
  nivovrije = millis();
}