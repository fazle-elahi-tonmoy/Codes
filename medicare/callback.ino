void write_callBack(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();
  Serial.printf("Received value = %d for %s - %s\n", val.val.i, device_name, param_name);
  param->updateAndReport(val);

  if (strcmp(device_name, "Drawer 1") == 0) {
    dr1 = val.val.b;
    if(!dr1) f1 = 1;
  }

  else if (strcmp(device_name, "Drawer 2") == 0) {
    dr2 = val.val.b;
    if(!dr2) f2 = 1;
  }

  else if (strcmp(device_name, "Drawer 3") == 0) {
    dr3 = val.val.b;
    if(!dr3) f3 = 1;
  }

  else if (strcmp(device_name, "Checkup") == 0) {
    if (strcmp(param_name, "Body Check") == 0) {
      b_check = val.val.b;
    }

    else if (strcmp(param_name, "Interval Period") == 0) {
      interval_period = val.val.i;
      EEPROM.write(0, interval_period);
      EEPROM.commit();
    }
  }

  else if (strcmp(device_name, "Notice") == 0) {
    if (strcmp(param_name, "SMS") == 0) {
      incoming_message = val.val.s;
      stage = 1;
      sms_timer = millis();
    }

    else if (strcmp(param_name, "Call") == 0) phoneCall = val.val.b;

    else if (strcmp(param_name, "Message to") == 0) {
      String phone = val.val.s;
      saveStringToEEPROM(1, phone);
      readStringFromEEPROM(1);
    }
  }
}