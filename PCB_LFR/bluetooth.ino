void bluetooth() {
  short int s = 10, spdl = 25, spdr = 25;
  char x;
  oled.clear(); oled.set2X(); text("ACTIVATED!", 04, 3);

  while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH) { //infinite loop
    if (Serial.available() > 0) {
      x = Serial.read();
      Serial.println(x);

      if (x == 'F') motor(s * spdl, s * spdr);
      else if (x == 'B') motor(-s * spdl, -s * spdr);
      else if (x == 'L') motor(-s * spdl, s * spdr);
      else if (x == 'R') motor(s * spdl, -s * spdr);
      else if (x == 'G') motor(0, s * spdr);
      else if (x == 'I') motor(s * spdl, 0);
      else if (x == 'H') motor(0, -s * spdr);
      else if (x == 'J') motor(-s * spdl, 0);
      else if (x == 'S') motor(0, 0);
      else if (x == 'U') digitalWrite(light, HIGH);
      else if (x == 'u') digitalWrite(light, LOW);
      else if (x == '0') s = 0;
      else if (x == '1') s = 1;
      else if (x == '2') s = 2;
      else if (x == '3') s = 3;
      else if (x == '4') s = 4;
      else if (x == '5') s = 5;
      else if (x == '6') s = 6;
      else if (x == '7') s = 7;
      else if (x == '8') s = 8;
      else if (x == '9') s = 9;
      else if (x == 'q') s = 10;
    }
  }
  intro();  motor(0, 0); digitalWrite(light, 0); 
  while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
}
