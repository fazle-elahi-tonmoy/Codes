byte menu() {
  byte cl = 0, b = 1, p = 8, sw, temp = 1, limit = 8;
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
    if (sw == 1 ) {
      temp++;
      if (temp > limit) {
        temp = 1; b = temp; p = b + 7;
      }
      else if (temp > p) {
        p = temp; b = p - 7;
      }
    }
    else if (sw == 2) {
      oled.setInvertMode(0); return temp;
    }
    sw = lswitch();
    if (sw == 1) {
      temp--;
      if (temp < 1) {
        temp = limit;  p = temp; b = p - 7;
      }
      else if (temp < b) {
        b = temp; p = b + 7;
      }
    }
    else if (sw == 2) {
      oled.setInvertMode(0); intro(); return 0;
    }
  }
}

String showmenu(byte a) {
  if (a == 1)      return "ADJUSTMENT      ";
  else if (a == 2)  return "CALLIBRATE      ";
  else if (a == 3) return "SENSOR TESTING  ";
  else if (a == 4) return "ANALOG READING  ";
  else if (a == 5) return "GO FORWARD      ";
  else if (a == 6) return "BLUETOOTH       ";
  else if (a == 7) return "SERVO TEST      ";
  else if (a == 8) return "U TURN TEST     ";
  else             return "NOTHING HERE!   ";
}
