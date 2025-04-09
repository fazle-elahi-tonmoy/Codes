void write_callBack(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  device_name = String(device->getDeviceName());
  param_name = String(param->getParamName());
  Serial.print(device_name + " -> " + param_name + ": ");

  if (param_name == "Phone Number" || param_name == "SMS") {
    incoming_message = val.val.s;
    Serial.println(incoming_message);
  }

  else {
    incoming_value = val.val.i;
    Serial.println(incoming_value);
  }
  callB = 1;
  param->updateAndReport(val);
}

void callBack_activate() {
  callB = 0;
  if (device_name[0] == 'S') {
    int i = device_name[7] - '1';
    state[i] = incoming_value;
    digitalWrite(sw_pins[i], state[i]);
  }

  if (param_name == "Security") security_state = security_check = incoming_value;

  if (param_name == "Phone Number") {
    saveStringToEEPROM(200, incoming_message);
    for (int i = 0; i < 11; i++) phone_number[i] = incoming_message[i];
    Serial.println("Phone Number Saved!");
  }

  if (param_name == "SMS") {
    stage = 1;
    sms_timer = millis();
  }

  if (param_name == "Alarm Trigger") {
    call_phone();
    delay(5000);
    trig.updateAndReportParam("Alarm Trigger", false);
  }
}