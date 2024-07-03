void drawer_update() {
  sensor();
  if (!s1 && (millis() - d1 > 5000) && f1) {
    f1 = 0;
    drawer1.write(max_pos);
    draw1.updateAndReportParam("Drawer 1 Status", "Drawer Closed");
  }
  if (!s2 && (millis() - d2 > 5000) && f2) {
    f2 = 0;
    drawer2.write(max_pos);
    draw2.updateAndReportParam("Drawer 2 Status", "Drawer Closed");
  }
  if (!s3 && (millis() - d3 > 5000) && f3) {
    f3 = 0;
    drawer3.write(max_pos);
    draw3.updateAndReportParam("Drawer 3 Status", "Drawer Closed");
  }

  if (s1) {
    d1 = millis();
    if (dr1) {
      dr1 = 0;
      alarm_active = 0;
      draw1.updateAndReportParam("Drawer 1 State", dr1);
    }
    if (!f1) draw1.updateAndReportParam("Drawer 1 Status", "Drawer Opened");
    f1 = 1;
    draw_flag = 0;
  }

  if (s2) {
    d2 = millis();
    if (dr2) {
      dr2 = 0;
      alarm_active = 0;
      draw2.updateAndReportParam("Drawer 2 State", dr2);
    }
    if (!f2) draw2.updateAndReportParam("Drawer 2 Status", "Drawer Opened");
    f2 = 1;
    draw_flag = 0;
  }

  if (s3) {
    d3 = millis();
    if (dr3) {
      dr3 = 0;
      alarm_active = 0;
      draw3.updateAndReportParam("Drawer 3 State", dr3);
    }
    if (!f3) draw3.updateAndReportParam("Drawer 3 Status", "Drawer Opened");
    f3 = 1;
    draw_flag = 0;
  }

  if (dr1) {
    if (!alarm_active) {
      oled.clear();
      text("   OPEN   ", 04, 02);
      text("TOP DRAWER", 04, 05);
      draw_out_timer = millis();
      draw_flag = 1;
    }
    drawer1.write(min_pos);
    d1 = millis();
    alarm_active = 1;
  }

  if (dr2) {
    if (!alarm_active) {
      oled.clear();
      text("   OPEN   ", 04, 02);
      text("MID DRAWER", 04, 05);
      draw_out_timer = millis();
      draw_flag = 1;
    }
    drawer2.write(min_pos);
    d2 = millis();
    alarm_active = 1;
  }

  if (dr3) {
    if (!alarm_active) {
      oled.clear();
      text("   OPEN   ", 04, 02);
      text("LOW DRAWER", 04, 05);
      draw_out_timer = millis();
      draw_flag = 1;
    }
    drawer3.write(min_pos);
    d3 = millis();
    alarm_active = 1;
  }
  if (!dr1 && !dr2 && !dr3) {
    alarm_active = 0;
    draw_flag = 0;
  }
  if ((millis() - draw_out_timer > 15000) && draw_flag) {
    message.updateAndReportParam("UPDATE", "DRAW NOT OPEN");
    draw_flag = 0;
  }
}
