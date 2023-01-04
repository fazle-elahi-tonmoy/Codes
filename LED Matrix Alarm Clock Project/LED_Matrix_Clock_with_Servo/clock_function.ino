int get_time() {
  dt = clock.getDateTime();
  hh = dt.hour;
  mm = dt.minute;
  ss = dt.second;
  return hh * 100 + mm;
}

int get_alarm() {
  a1 = clock.getAlarm1();
  hh = a1.hour;
  mm = a1.minute;
  ss = a1.second;
  return hh * 100 + mm;
}

int get_date() {
  dt = clock.getDateTime();
  DD = dt.day;
  MM = dt.month;
  YY = dt.year;
  return DD * 100 + MM;
}

int get_alarm_2() {
  a2 = clock.getAlarm2();
  hh = a2.hour;
  mm = a2.minute;
  ss = a2.second;
  return hh * 100 + mm;
}

int get_initial() {
  hh = EEPROM.read(0);
  mm = EEPROM.read(1);
  if (hh > 24) {
    hh = 0; EEPROM.write(0, hh);
  }
  if (mm > 60) {
    mm = 0; EEPROM.write(1, mm);
  }
  return hh * 100 + mm;
}

int t_diff(int a, int b) {
  int hh1 = a / 100, mm1 = a % 100, hh2 = b / 100, mm2 = b % 100;
  int mm = mm1 - mm2;
  if (mm < 0) {
    mm += 60; hh2++;
  }
  int hh = hh1 - hh2;
  if(hh < 0) hh += 24;
  return hh * 100 + mm;
}
