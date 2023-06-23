void write_callBack(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();
  if (strcmp(device_name, "Light") == 0) {
    Serial.printf("Received value = %d for %s - %s\n", val.val.i, device_name, param_name);
    if (strcmp(param_name, "Power") == 0) {
      bulb_state = val.val.b;
      digitalWrite(bulb_switch, !bulb_state);
      param->updateAndReport(val);
    }
    if (strcmp(param_name, "Bulb Timer") == 0) {
      bulb_time = val.val.i;
      param->updateAndReport(val);
    }
    if (strcmp(param_name, "Timer Activation") == 0) {
      bulb_timer = val.val.b;
      param->updateAndReport(val);
    }
  }

  else if (strcmp(device_name, "Socket") == 0) {
    Serial.printf("Received value = %d for %s - %s\n", val.val.i, device_name, param_name);
    if (strcmp(param_name, "Power") == 0) {
      socket_state = val.val.b;
      digitalWrite(socket_switch, socket_state);
      param->updateAndReport(val);
    }
    if (strcmp(param_name, "Socket Timer") == 0) {
      socket_time = val.val.i;
      param->updateAndReport(val);
    }
    if (strcmp(param_name, "Timer Activation") == 0) {
      socket_timer = val.val.b;
      param->updateAndReport(val);
    }
  }

  else if (strcmp(device_name, "Sign Board") == 0) {
    // Serial.printf("Received value = %d for %s - %s\n", val.val.s, device_name, param_name);
    oled.clear();
    oled.setCursor(4, 3);
    oled.print(val.val.s);
    signboard = 1;
    param->updateAndReport(val);
  }
}


void timer_parameter_update() {
  bulb.updateAndReportParam("Timer Activation", bulb_timer);
  bulb.updateAndReportParam("Bulb Timer", bulb_time);
  socket.updateAndReportParam("Timer Activation", socket_timer);
  socket.updateAndReportParam("Socket Timer", socket_time);
}