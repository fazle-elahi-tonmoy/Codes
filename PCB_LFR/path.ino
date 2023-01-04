void counter_display() {
  byte cl = 100, sw, temp = counter, limit = 99;
  oled.set2X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      value = String(temp);
      text("COUNTER:" + value + " ", 04, 3);
    }
    sw = rswitch();
    if (sw == 1 && temp < limit) temp++;
    else if (sw == 2) {
      counter = temp;
      EEPROM.write(19, counter); delay(10);
      break;
    }
    sw = lswitch();
    if (sw == 1 && temp > 0) temp--;
    else if (sw == 2) break;
  }
  intro();
}

String show_path(byte a) {
  if (a == 1) return "NOTHING   ";
  else if (a == 2) return "LEFT      ";
  else if (a == 3) return "STRAIGHT  ";
  else if (a == 4) return "RIGHT     ";
  else if (a == 5) return "WHITE     ";
  else if (a == 6) return "GRAB      ";
  else if (a == 7) return "RELEASE   ";
  else return "GARBAGE   ";

}

void path_select() {
  byte cl = 0, b = 1, p = 8, sw, temp = 1, limit = 99;
  oled.set1X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      for (byte i = b; i <= p && i <= limit; i++) {
        (i == cl) ? oled.setInvertMode(1) : oled.setInvertMode(0);
        value = String(i, 10) + ". " + show_path(path[i - 1]) + "          ";
        text(value, 0, i - b);
      }
    }
    sw = rswitch();
    if (sw == 1 && temp < limit) {
      temp++;
      if (temp > p) {
        p = temp; b = p - 7;
      }
    }
    else if (sw == 2) {
      oled.setInvertMode(0); change_path(temp, 7); cl = 0;
    }
    sw = lswitch();
    if (sw == 1 && temp > 1) {
      temp--;
      if (temp < b) {
        b = temp; p = b + 7;
      }
    }
    else if (sw == 2) {
      oled.setInvertMode(0); intro(); return 0;
    }
  }
}

void change_path(int a, int b) {
  byte cl = 0, sw, temp = EEPROM.read(19 + a), limit = b;
  oled.set2X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      value = show_path(temp);
      text(value, 04, 3);
    }
    sw = rswitch();
    if (sw == 1 && temp < limit) temp++;
    else if (sw == 2) {
      EEPROM.write(19 + a, temp); delay(10); path[a - 1] = temp; break;
    }
    sw = lswitch();
    if (sw == 1 && temp > 1) temp--;
    else if (sw == 2) break;
  }
  oled.clear(); oled.set1X();
}
