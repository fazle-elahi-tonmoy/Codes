String show_path(byte a) {
  if (a == 0) return "NOTHING   ";
  else if (a == 1) return "LEFT      ";
  else if (a == 2) return "RIGHT     ";
  else if (a == 3) return "STRAIGHT  ";
  else if (a == 4) return "GRAB 6cm  ";
  else if (a == 5) return "GRAB 3cm  ";
  else if (a == 6) return "RELEASE   ";
  else if (a == 7) return "LOW SPEED ";
  else if (a == 8) return "90 GRAB 6 ";
  else if (a == 9) return "90 GRAB 3 ";
  else if (a == 10)return "90 RELEASE";
  else if (a == 11)return "90 COUNT  ";
  else return "GARBAGE   ";

}

void path_select() {
  byte cl = 0, b = 1, p = 8, sw, temp = 1, limit = 50;
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
      change_path(temp); cl = 0;
    }
    sw = lswitch();
    if (sw == 1 && temp > 1) {
      temp--;
      if (temp < b) {
        b = temp; p = b + 7;
      }
    }
    else if (sw == 2) break;
  }
  oled.setInvertMode(0);
  intro();
}

void change_path(int a) {
  byte cl = 100, sw, temp = EEPROM.read(29 + a), limit = 11;
  oled.set2X(); oled.clear(); oled.setInvertMode(0);
  while (1) {
    if (cl != temp) {
      cl = temp;
      value = show_path(temp);
      text(value, 04, 3);
    }
    sw = rswitch();
    if (sw == 1 && temp < limit) temp++;
    else if (sw == 2) {
      EEPROM.write(29 + a, temp); delay(10); path[a - 1] = temp; break;
    }
    sw = lswitch();
    if (sw == 1 && temp > 0) temp--;
    else if (sw == 2) break;
  }
  oled.clear(); oled.set1X();
}

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
