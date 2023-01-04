byte menu() {
  byte cl = 0, b = 1, p = 8, sw, temp = 1, limit = 5;
  oled.set1X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      for (byte i = b; i <= p && i <= limit; i++) {
        (i == cl) ? oled.setInvertMode(1) : oled.setInvertMode(0);
        value = String(i, 10) + ". " + showmenu(i);
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
      oled.setInvertMode(0); return temp;
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

String showmenu(byte a) {
  if (a == 1) return "LINE FOLLOW        ";
  else if (a == 2) return "SENSOR READING     ";
  else if (a == 3) return "ANALOG READING     ";
  else if (a == 4) return "STRAIGHT RUN       ";
  else if (a == 5) return "BLUETOOTH CONTROL  ";
  else return "NOTHING YET!       ";
}
