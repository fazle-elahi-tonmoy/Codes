void clock_update() {
  current_time = get_time();
  display_value(current_time);
}

void alarm_update() {
  current_alarm = get_alarm();
  display_value(current_alarm);
}

void special_alarm_update_1() {
  s_alarm_1 = get_initial();
  display_value(s_alarm_1);
}

void special_alarm_update_2() {
  s_alarm_2 = get_alarm_2();
  display_value(s_alarm_2);
}

void temp_update() {
  if (millis() - tm > temp_interval * 1000) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
    tm = millis();
  }
}
