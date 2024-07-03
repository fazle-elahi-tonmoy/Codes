void WiFi_scan() {
  int strength[3] = { -255, -255, -255 };
  int n = WiFi.scanNetworks();
  if (n == 0) return;
  else {
    int found = 0;
    for (int i = 0; i < n; i++) {
      String WiFi_name = WiFi.SSID(i);
      // Serial.println(WiFi_name);
      if (WiFi_name == WiFi1) strength[0] = WiFi.RSSI(i);
      if (WiFi_name == WiFi2) strength[1] = WiFi.RSSI(i);
      if (WiFi_name == WiFi3) strength[2] = WiFi.RSSI(i);
    }
  }
  display.clearDisplay();
  for (int i = 0; i < 3; i++) {
    display.setCursor(0, i * 24);
    display.print(String(i) + ") ");
    display.print(strength[i]);
    display.print(" dB");
    String v = String(strength[i]);
    int length = v.length();
    for (byte i = 0; i < length; i++) Serial1.write(v[i]);
    (i < 2)? Serial1.write(','):Serial1.write(';');
  }
  display.display();
  home = 0;
  refresh = millis();
}