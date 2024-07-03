void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
      printQR(service_name, pop, "ble");
      oled.clear();
      text("SETUP MODE", 4, 0);
      text("   SCAN   ", 4, 3);
      text(" QR CODE ", 11, 6);
      homepage = 0;
      refresh = 1;
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      oled.clear();
      text("CONNECTED", 11, 2);
      homepage = 1;
      refresh = 1;
      t1 = millis();
      break;
    case ARDUINO_EVENT_PROV_INIT:
      wifi_prov_mgr_disable_auto_stop(10000);
      break;
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
      oled.clear();
      text("  READY  ", 11, 2);
      homepage = 1;
      refresh = 1;
      t1 = millis();
      wifi_prov_mgr_stop_provisioning();
      break;
  }
}