void clock_update() {
  current_time = get_time();
  display_value(current_time);
}

void alarm_update() {
  current_alarm = get_alarm();
  display_value(current_alarm);
}

void date_update() {
  current_date = get_date();
  display_value(current_date);
}
