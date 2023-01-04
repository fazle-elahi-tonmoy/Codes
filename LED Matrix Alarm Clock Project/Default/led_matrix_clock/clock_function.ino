int get_time(){
  dt = clock.getDateTime();
  hh = dt.hour;
  mm = dt.minute;
  ss = dt.second;
  return hh * 100 + mm;
}

int get_date(){
  dt = clock.getDateTime();
  DD = dt.day;
  MM = dt.month;
  YY = dt.year;
  return DD * 100 + MM;
}
