String show_adjust(byte a) {
  if (a == 1)      return "TOP SPEED      ";
  else if (a == 2) return "LEFT ERROR     ";
  else if (a == 3) return "RIGHT ERROR    ";
  else if (a == 4) return "STRAIGHTNER    ";
  else if (a == 5) return "FULL BRAKE     ";
  else if (a == 6) return "TURN BRAKE     ";
  else if (a == 7) return "TURN SPEED     ";
  else if (a == 8) return "NODE DELAY     ";
  else if (a == 9) return "END LINE DELAY ";
  else if (a == 10) return "U TURN DELAY  ";
}

void adjustment_menu() {
  byte cl = 0, b = 1, p = 8, sw, temp = 1, limit = 10;
  oled.set1X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      for (byte i = b; i <= p && i <= limit; i++) {
        (i == cl) ? oled.setInvertMode(1) : oled.setInvertMode(0);
        value = String(i) + ". " + show_adjust(i) + String(EEPROM.read(i + 17)) + "  ";
        text(value, 2, i - b);
      }
    }
    sw = rswitch();
    if (sw == 1) {
      temp++;
      if (temp > limit) {
        temp = 1; b = temp; p = b + 7;
      }
      else if (temp > p) {
        p = temp; b = p - 7;
      }
    }
    else if (sw == 2) {
      oled.setInvertMode(0); adjustment(temp); cl = 0;
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
      oled.setInvertMode(0); break;
    }
  }
  sp = EEPROM.read(18);
  le = EEPROM.read(19);
  re = EEPROM.read(20);
  dt = EEPROM.read(21);
  br = EEPROM.read(22);
  tbr = EEPROM.read(23);
  tsp = EEPROM.read(24);
  node = EEPROM.read(25);
  epoint = EEPROM.read(26);
  turn = EEPROM.read(27);
  spl = sp - le;
  spr = sp - re;
  intro();
}

void adjustment(byte a) {
  byte cl = 255, sw, temp = EEPROM.read(17 + a), limit = 250;
  oled.set2X(); oled.clear();
  while (1) {
    if (cl != temp) {
      cl = temp;
      value = "SET: " + String(temp) + "    ";
      text(value, 04, 3);
    }
    sw = rswitch();
    if (sw == 1 && temp < limit) (a > 4) ? temp += 10 : temp++;
    else if (sw == 2) {
      EEPROM.write(17 + a, temp); delay(10); break;
    }
    sw = lswitch();
    if (sw == 1 && temp > 0) (a > 4) ? temp -= 10 : temp--;
    else if (sw == 2) break;
  }
  oled.clear(); oled.set1X();
}
