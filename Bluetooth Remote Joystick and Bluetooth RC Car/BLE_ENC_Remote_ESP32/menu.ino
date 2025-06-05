byte menu() {
  display.clearDisplay();
  short int cl = 255, b = 0, list = 9, temp = 0;
  while (1) {
    if (cl != temp) {
      cl = temp;
      display_icon(b, cl);
      String value = menu_options(cl + 1);
      byte charlen = value.length();
      String disp;
      for (int i = 0; i < (10 - charlen) / 2; i++) disp += " ";
      disp += value;
      (charlen % 2) ? text(disp, 11, 46) : text(disp, 4, 46);
      display.display();
    }
    byte l = Lencoder_read();
    byte r = Rencoder_read();
    if (r == 1 || l == 1) {
      playNote(selectionMelody[3], 50);
      temp++;
      if (temp > list) {
        temp = 0;
        b = 0;
      } else if (temp > b + 3) b++;
    }

    else if (r == 2 || l == 2) {
      playNote(selectionMelody[3], 50);
      temp--;
      if (temp < 0) {
        temp = list;
        b = list - 3;
      } else if (temp < b) b--;
    }


    if (push(r1)) return cl + 1;
    if (push(l1)) return 0;
  }
}

String menu_options(byte x) {
  if (x == 1) return "RC MODE";
  else if (x == 2) return "PC CONSOLE";
  else if (x == 3) return "CALIBRATE";
  else if (x == 4) return "POT CHECK";
  else if (x == 5) return "PUSH READ";
  else if (x == 6) return "SYS TEST";
  else if (x == 7) return "SNAKE GAME";
  else if (x == 8) return "DX BALL";
  else if (x == 9) return "SPACE GAME";
  else if (x == 10) return "MOTO RACE";
  else return "ERROR";
}