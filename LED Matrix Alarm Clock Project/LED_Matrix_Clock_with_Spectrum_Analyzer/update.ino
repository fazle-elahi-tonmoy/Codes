void clock_update() {
  current_time = get_time();
  big_display(current_time);
}

void alarm_update() {
  current_alarm = get_alarm();
  big_display(current_alarm);
}
