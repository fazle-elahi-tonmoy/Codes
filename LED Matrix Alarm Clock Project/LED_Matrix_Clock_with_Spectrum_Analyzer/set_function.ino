void set_time() {
  bool panel_section = 1; bool state = 1, flag = 0, flag2 = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state;
      lc.shutdown(panel_section * 2, state);
      lc.shutdown(panel_section * 2 + 1, state);
    }
    flag = set_press(flag);
    if (flag) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); m1 = millis();
      (panel_section) ? current_time += 100 : current_time += 1;
      if ((current_time / 100) >= 24) current_time -= 2400;
      if ((current_time % 100) >= 60) current_time -= 60;
      big_display(current_time);
    }

    flag2 = back_press(flag2);
    if (flag2) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); m1 = millis();
      (panel_section) ? current_time -= 100 : current_time -= 1;
      if (current_time < 0) current_time += 2400;
      if ((current_time % 100) >= 60) current_time -= 40;
      big_display(current_time);
    }

    int r = menu_press(0);
    if (r == 2) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0);
      panel_section = !panel_section;
    }
    else if (r == 1) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); break;
    }
  }
  hh = current_time / 100; mm = current_time % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
}

void set_alarm() {
  bool panel_section = 1; bool state = 1, flag = 0, flag2 = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state;
      lc.shutdown(panel_section * 2, state);
      lc.shutdown(panel_section * 2 + 1, state);
    }
    flag = set_press(flag);
    if (flag) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); m1 = millis();
      (panel_section) ? current_alarm += 100 : current_alarm += 1;
      if ((current_alarm / 100) >= 24) current_alarm -= 2400;
      if ((current_alarm % 100) >= 60) current_alarm -= 60;
      big_display(current_alarm);
    }
    flag2 = back_press(flag2);
    if (flag2) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); m1 = millis();
      (panel_section) ? current_alarm -= 100 : current_alarm -= 1;
      if (current_alarm < 0) current_alarm += 2400;
      if ((current_alarm % 100) >= 60) current_alarm -= 40;
      big_display(current_alarm);
    }
    int r = menu_press(0);
    if (r == 2) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0);
      panel_section = !panel_section;
    }
    else if (r == 1) {
      lc.shutdown(panel_section * 2, 0);
      lc.shutdown(panel_section * 2 + 1, 0); break;
    }
  }
  hh = current_alarm / 100; mm = current_alarm % 100;
  clock.setAlarm1(0, hh, mm, 00, DS3231_MATCH_H_M_S);
  menu_count = 1;
}
