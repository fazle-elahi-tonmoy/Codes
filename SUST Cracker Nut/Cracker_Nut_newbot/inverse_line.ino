void inverse_y() {
  if (sensor [0] == 1 && sensor [5] == 1 && (sensor [1] == 0 || sensor [2] == 0 || sensor [3] == 0 || sensor [4] == 0)) {
    m82 = m81 = millis();
    mos (50, 50);
    while ((sensor [0] == 1 || sensor [5] == 1) && (sensor [1] == 0 || sensor [2] == 0 || sensor [3] == 0 || sensor [4] == 0)) {
      check();
      m82 = millis();
      if (m82 - m81 >= rtd && rtd != 0) {
        if (mode == 1) {
          mode = 0;
          display.clearDisplay();
          text(" REVERSE ", 10, 24);
          display.display();
        }
        else {
          mode = 1;
          text_line_follow();
        }
        mov = 0;
        cross = 0;
        return;
      }
    }
    (side == 1) ? mov = 1 : mov = 2;
    (side == 1) ? k90 = 1 : k90 = 2;
  }
}
