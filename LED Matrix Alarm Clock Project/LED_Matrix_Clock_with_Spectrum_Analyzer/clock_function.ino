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
