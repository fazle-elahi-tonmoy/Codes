void write_callBack(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();
  Serial.print(device_name);
  Serial.print(" ");
  Serial.println(param_name);

  if (device_name[0] == 'L') {
    switch_state = val.val.b;
    byte i = device_name[6] - '1';
    state[i] = switch_state;
  }

  else if (device_name[0] == 'F') {
    switch_state = val.val.b;
    byte i = device_name[4] - '1';
    state[i + 7] = switch_state;
  }

  else if (device_name[0] == 'E') {
    switch_state = val.val.b;
    byte i = device_name[3] - '1';
    state[i + 11] = switch_state;
  }

  else if (strcmp(device_name, "Security") == 0) {
    if (strcmp(param_name, "Security") == 0) security_state = security_check = val.val.b;

    else if (strcmp(param_name, "Phone Number") == 0) {
      String phone = val.val.s;
      saveStringToEEPROM(1, phone);
      readStringFromEEPROM(1);
    }

    else if (strcmp(param_name, "SMS") == 0) {
      incoming_message = val.val.s;
      stage = 1;
      sms_timer = millis();
    }

    else if (strcmp(param_name, "Call") == 0) phoneCall = val.val.b;
    delay(1000);
  }

  param->updateAndReport(val);
}