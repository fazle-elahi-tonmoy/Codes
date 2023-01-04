void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
      printQR(service_name, pop, "ble");
      homepage = false;
      oled.clear();
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      homepage = true;
      oled.clear();
      break;
    case ARDUINO_EVENT_PROV_INIT:
      wifi_prov_mgr_disable_auto_stop(10000);
      break;
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
      homepage = true;
      oled.clear();
      wifi_prov_mgr_stop_provisioning();
      break;
  }
}