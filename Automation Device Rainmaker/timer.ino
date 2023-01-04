void set_timer(byte a) {
  oled.clear();
  int r;
  String value;
  if ((a == 1 && bulb_timer) || (a == 2 && socket_timer)) {
    (a == 1) ? value = String(bulb_time) : value = String(socket_time);
    text(value + "m", 76, 2);
    text("TIMER:", 4, 2);
    text("Clear Back", 4, 6);
    while (1) {
      r = press(lbutton);
      if (r == 2) {
        if (a == 1) bulb_time = bulb_timer = 0;
        else socket_time = socket_timer = 0;
        oled.clear();
        text(" CLEARED! ", 4, 4);
        timer_parameter_update();
        delay(1000);
        break;
      }
      r = press(rbutton);
      if (r == 2) break;
    }
  }

  else if ((a == 1 && !bulb_timer) || (a == 2 && !socket_timer)) {
    text("Set   Back", 4, 6);
    while (1) {
      (a == 1) ? value = String(bulb_time) : value = String(socket_time);
      text(value + "m", 76, 2);
      text("TIME: ", 4, 2);
      r = press(lbutton);
      if (r == 1) {
        if (a == 1 && bulb_time > 0) bulb_time -= 15;
        else if (a == 2 && socket_time > 0) socket_time -= 15;
      }

      else if (r == 2) {
        (a == 1) ? bulb_timer = 1 : socket_timer = 1;
        oled.clear();
        text("TIMER SET!", 4, 4);
        timer_parameter_update();
        delay(1000);
        break;
      }

      r = press(rbutton);
      if (r == 1) {
        (a == 1) ? bulb_time += 15 : socket_time += 15;
      }

      else if (r == 2) {
        (a == 1) ? bulb_time = 0 : socket_time = 0;
        oled.clear();
        text("   BYE!   ", 4, 4);
        delay(1000);
        break;
      }
    }
  }
  oled.clear();
}


void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    text("CLOCK FAIL", 4, 1);
    return;
  }
  oled.setCursor(4, 1);
  oled.print(" ");
  oled.print(&timeinfo, "%I:%M:%S");
  oled.println(" ");
  // char timeHour[3];
  // strftime(timeHour,3, "%H", &timeinfo);
}