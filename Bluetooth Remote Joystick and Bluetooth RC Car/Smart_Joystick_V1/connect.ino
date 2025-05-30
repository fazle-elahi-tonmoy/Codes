void connection_panel() {
  display.clearDisplay();
  display.setTextSize(1);
  short int cl = 1, temp = 0;
  while (1) {
    if (cl != temp) {
      display.clearDisplay();
      cl = temp;
      for (byte i = 0; i < 8; i++) {
        (cl == i) ? display.setTextColor(0, 1) : display.setTextColor(1);
        if (i == 0) text("  Test Remote Data   ", 1, 0);
        else {
          text(String(i) + ") " + readStringFromEEPROM(i * 11), 04, i * 8);
        }
      }
      display.display();
    }
    byte l = Lencoder_read();
    byte r = Rencoder_read();
    if (r == 1 || l == 1) {
      playNote(selectionMelody[3], 50);
      temp++;
      if (temp > 7) temp = 0;
    }

    else if (r == 2 || l == 2) {
      playNote(selectionMelody[3], 50);
      temp--;
      if (temp < 0) temp = 7;
    }


    if (push(r1)) {
      send_data(cl);
      return;
    }
    if (push(l1)) return;
    if (push(lb) || push(rb)) {
      if (cl != 0) name_adjust(cl);
      display.setTextSize(1);
      cl = 0;
    }
  }
}

void name_adjust(byte a) {
  display.setTextSize(2);
  display.setTextColor(1);
  for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
  byte limit[4][2] = {
    { 65, 90 },
    { 97, 122 },
    { 48, 57 },
    { 33, 47 },
  };
  String value = readStringFromEEPROM(a * 11);
  int length = value.length();
  for (int i = 0; i < 10 - length; i++) value += '\0';
  short int cl = 1, temp = 0;
  byte case_no = 1;
  bool refresh = 0;
  while (1) {
    if (cl != temp || refresh) {
      cl = temp;
      refresh = 0;
      display.clearDisplay();
      display.setTextSize(2);
      text(value, 04, 24);
      text("_", 04 + cl * 12, 30);
      display.setTextSize(1);
      if (case_no == 1) text("        ABCD         ", 02, 56);
      else if (case_no == 2) text("        abcd         ", 02, 56);
      else if (case_no == 3) text("        1234         ", 02, 56);
      else if (case_no == 4) text("        +-*/         ", 02, 56);
      display.display();
    }


    byte l = Lencoder_read();
    byte r = Rencoder_read();

    if (l == 1) {
      temp++;
      if (temp > 9) temp = 9;
    }

    if (l == 2) {
      temp--;
      if (temp < 0) temp = 0;
    }

    if (r) {
      char x = value[cl];
      if (case_no == 1) {
        if (x >= 97 && x <= 122) x -= 32;
        else if (x >= 65 && x <= 90)
          ;
        else x = 65;
      }


      else if (case_no == 2) {
        if (x >= 97 && x <= 122)
          ;
        else if (x >= 65 && x <= 90) x += 32;
        else x = 97;
      }

      else if (case_no == 3) {
        if (x < 48 || x > 57) x = 48;
      }

      else if (case_no == 4) {
        if (x < 33 || x > 47) x = 33;
      }

      if (r == 1) {
        x++;
        if (x > limit[case_no - 1][1]) x = limit[case_no - 1][1];
      }

      if (r == 2) {
        x--;
        if (x < limit[case_no - 1][0]) x = limit[case_no - 1][0];
      }
      refresh = 1;
      value[cl] = x;
    }

    if (push(rb)) {
      for (int i = 9;; i--) {
        if (i == cl) break;
        else value[i] = value[i - 1];
      }
      value[cl] = ' ';
      temp++;
      if (temp > 9) temp = 9;
    }

    else if (push(lb)) {
      for (int i = cl; i < 9; i++) {
        value[i] = value[i + 1];
      }
      value[9] = '\0';
      refresh = 1;
    }

    if (push(er)) {
      case_no++;
      if (case_no > 4) case_no = 1;
      refresh = 1;
    }

    if (push(el)) {
      case_no--;
      if (case_no < 1) case_no = 4;
      refresh = 1;
    }

    if (push(r1)) {
      saveStringToEEPROM(a * 11, value);
      return;
    }
    if (push(l1)) return;
  }
}