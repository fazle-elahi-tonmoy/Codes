void write_callback(Device *device, Param *param, const param_val_t val,
                    void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();

  if (strcmp(device_name, "Bulb") == 0) {
    if (strcmp(param_name, "Power") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      bulb_state = val.val.b;
      (bulb_state == false) ? digitalWrite(bulb_pin, LOW) : digitalWrite(bulb_pin, HIGH);
      param->updateAndReport(val);
    }

    if (strcmp(param_name, "Automation") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      bulb_auto = val.val.b;
      param->updateAndReport(val);
    }
  }

  if (strcmp(device_name, "Fan") == 0) {
    if (strcmp(param_name, "Power") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      fan_state = val.val.b;
      (fan_state == false) ? ledcWrite(fan_channel, 0) : ledcWrite(fan_channel, fan_speed);
      param->updateAndReport(val);
    }

    if (strcmp(param_name, "Speed") == 0) {
      Serial.printf("Received value = %d for %s - %s\n", val.val.i, device_name, param_name);
      int fansp = val.val.i * 50;
      (fan_state == false) ? ledcWrite(fan_channel, fansp) : ledcWrite(fan_channel, fansp);
      param->updateAndReport(val);
    }
  }

  if (strcmp(device_name, "Security") == 0) {
    if (strcmp(param_name, "Buzzer State") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      digitalWrite(buzzer, val.val.b);
      param->updateAndReport(val);
    }

    if (strcmp(param_name, "Security Mode") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      security_mode = val.val.b;
      param->updateAndReport(val);
    }

    if (strcmp(param_name, "Theft Detection") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      theft_detect = val.val.b;
      param->updateAndReport(val);
    }
  }

  if (strcmp(device_name, "Window") == 0) {
    if (strcmp(param_name, "Window Closed") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b ? "true" : "false", device_name, param_name);
      window_state = val.val.b;
      (!window_state) ? window.write(window_open) : window.write(window_close);
      param->updateAndReport(val);
    }
  }
}