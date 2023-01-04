void set_time() {
  bool panel_section = 1; bool state = 1, flag = 0;
  m1 = millis();
  while (1) {
    if (millis() - m1 > 500) {
      m1 = millis(); state = !state; lc.shutdown(panel_section, state);
    }
    flag = set_press(flag);
    if (flag) {
      if(state) lc.shutdown(panel_section, 0); m1 = millis();
      (panel_section) ? current_time += 100 : current_time += 1;
      if ((current_time / 100) >= 24) current_time -= 2400;
      if ((current_time % 100) >= 60) current_time -= 60;
      display_value(current_time);
    }
    int r = menu_press(0);
    if(r == 1){
      lc.shutdown(panel_section, 0);
      panel_section = !panel_section;
    }
    else if(r == 2) {
      lc.shutdown(panel_section, 0); break;
    }
  }
  get_date();
  hh = current_time/100; mm = current_time % 100;
  clock.setDateTime(YY, MM, DD, hh, mm, 00);
}
