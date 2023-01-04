void clock_update() {
  current_time = get_time();
  display_value(current_time);
}

void date_update() {
  if (current_date != get_date() || stability) {
    stability = 0;
    current_date = get_date();
    display_value(current_date);
  }
}
