void set_time() {
  bool panel_section = 1; bool state = 1, flag = 0; 
  m1 = m3 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = m3 = millis();
      (panel_section) ? current_time += 100 : current_time += 1;
      if ((current_time / 100) >= 24) current_time -= 2400;
      if ((current_time % 100) >= 60) current_time -= 60;
      display_value(current_time);
    }
    int r = tap_press() ;
    if (r >= 2) {
      lc.shutdown(panel_section, 0); break;
    }
    else if (r != 0) {
      m1 = m3 = millis();
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    if (millis() - m3 > return_time * 1000) {
      lc.shutdown(panel_section, 0);
      menu_count = 1; return;
    }
  }
  get_date();
  hh = current_time / 100; mm = current_time % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
  clock.armAlarm1(true);
}

void set_alarm() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = m3 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = m3 = millis();
      (panel_section) ? current_alarm += 100 : current_alarm += 1;
      if ((current_alarm / 100) >= 24) current_alarm -= 2400;
      if ((current_alarm % 100) >= 60) current_alarm -= 60;
      display_value(current_alarm);
    }
    int r = tap_press() ;
    if (r >= 2) {
      lc.shutdown(panel_section, 0); break;
    }
    else if (r != 0) {
      m1 = m3 = millis();
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    if (millis() - m3 > return_time * 1000) {
      lc.shutdown(panel_section, 0);
      menu_count = 1; current_alarm = get_alarm();
      return;
    }
  }
  menu_count = 1;
  hh = current_alarm / 100; mm = current_alarm % 100;
  clock.setAlarm1(0, hh, mm, 00, DS3231_MATCH_H_M_S);
  m3 = millis();
  while (millis() - m3 < wait_after_alarm_setup * 1000);
}

void set_date() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = m3 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = millis();
      (panel_section) ? current_date += 100 : current_date += 1;
      if ((current_date / 100) > 31) current_date -= 3100;
      if ((current_date % 100) > 12) current_date -= 12;
      display_value(current_date);
    }
    int r = tap_press() ;
    if (r >= 2) {
      lc.shutdown(panel_section, 0); break;
    }
    else if (r != 0) {
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    if (millis() - m3 > return_time * 1000) {
      lc.shutdown(panel_section, 0);
      menu_count = 1; return;
    }
  }
  get_time(); get_date();
  hh = current_date / 100; mm = current_date % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
}
