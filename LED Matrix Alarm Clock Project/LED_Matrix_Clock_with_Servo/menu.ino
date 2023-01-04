void menu(byte a) {
  switch (a) {
    case 1: clock_update(); break;
    case 2: alarm_update(); break;
    case 3: date_update(); break;
    case 4: special_alarm_update_1(); break;
    case 5: special_alarm_update_2(); break;
    case 6: display_value(f * 100); break;
    case 7: display_value(t * 100); break;
    case 8: display_value(h * 100); break;
  }
}
