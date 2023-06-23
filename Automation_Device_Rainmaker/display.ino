void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}

void home_screen() {
  if (homepage && !signboard) {
    if (WiFi.status() != WL_CONNECTED) text(" NO WiFi ", 11, 1);
    else if (millis() - t2 > 1000) {
      t2 = millis();
      printLocalTime();
    }
    (socket_state) ? text("ON ", 86, 6) : text("OFF", 86, 6);
    (bulb_state) ? text("ON ", 4, 6) : text("OFF", 4, 6);
  }

  else if(!signboard) {
    text("SETUP MODE", 4, 1);
    text("   SCAN   ", 4, 4);
    text(" QR CODE ", 11, 6);
  }
}