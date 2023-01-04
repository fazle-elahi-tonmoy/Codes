void set_time() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = millis();
      (panel_section) ? current_time += 100 : current_time += 1;
      if ((current_time / 100) >= 24) current_time -= 2400;
      if ((current_time % 100) >= 60) current_time -= 60;
      display_value(current_time);
    }
    int r = menu_press(0);
    if (r == 2) {
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    else if (r == 1) {
      lc.shutdown(panel_section, 0); break;
    }
  }
  get_date();
  hh = current_time / 100; mm = current_time % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
}

void set_alarm() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = millis();
      (panel_section) ? current_alarm += 100 : current_alarm += 1;
      if ((current_alarm / 100) >= 24) current_alarm -= 2400;
      if ((current_alarm % 100) >= 60) current_alarm -= 60;
      display_value(current_alarm);
    }
    int r = menu_press(0);
    if (r == 2) {
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    else if (r == 1) {
      lc.shutdown(panel_section, 0); break;
    }
  }
  hh = current_alarm / 100; mm = current_alarm % 100;
  clock.setAlarm1(0, hh, mm, 00, DS3231_MATCH_H_M_S);
}

void set_date() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = millis();
      (panel_section) ? current_date += 100 : current_date += 1;
      if ((current_date / 100) >= 24) current_date -= 2400;
      if ((current_date % 100) >= 60) current_date -= 60;
      display_value(current_date);
    }
    int r = menu_press(0);
    if (r == 2) {
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    else if (r == 1) {
      lc.shutdown(panel_section, 0); break;
    }
  }
  get_time(); get_date();
  hh = current_date / 100; mm = current_date % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
}
