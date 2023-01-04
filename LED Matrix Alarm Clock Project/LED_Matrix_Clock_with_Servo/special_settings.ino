void set_alarm2() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = m3 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = m3 = millis();
      (panel_section) ? s_alarm_2 += 100 : s_alarm_2 += 1;
      if ((s_alarm_2 / 100) >= 24) s_alarm_2 -= 2400;
      if ((s_alarm_2 % 100) >= 60) s_alarm_2 -= 60;
      display_value(s_alarm_2);
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
      menu_count = 1; s_alarm_2 = get_alarm_2();
      return;
    }
  }
  menu_count = 1;
  hh = s_alarm_2 / 100; mm = s_alarm_2 % 100;
  clock.setAlarm2(0, hh, mm, 00, DS3231_MATCH_H_M_S);
  m3 = millis();
  while (millis() - m3 < wait_after_alarm_setup * 1000);
}

void set_start_time() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = m3 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if (state) lc.shutdown(panel_section, 0); m1 = m3 = millis();
      (panel_section) ? s_alarm_1 += 100 : s_alarm_1 += 1;
      if ((s_alarm_1 / 100) >= 24) s_alarm_1 -= 2400;
      if ((s_alarm_1 % 100) >= 60) s_alarm_1 -= 60;
      display_value(s_alarm_1);
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
      menu_count = 1; s_alarm_1 = get_initial();
      return;
    }
  }
  menu_count = 1;
  hh = s_alarm_1 / 100; mm = s_alarm_1 % 100;
  EEPROM.write(0, hh); EEPROM.write(1, mm); clock.armAlarm2(1);
  m3 = millis();
  while (millis() - m3 < wait_after_alarm_setup * 1000);
}
