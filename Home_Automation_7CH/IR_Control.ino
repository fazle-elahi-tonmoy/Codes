void IR_Control() {
  int received = 0;
  if (IrReceiver.decode() && !ir_flag) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) IrReceiver.resume();
    else received = IrReceiver.decodedIRData.command;
    Serial.println(received, HEX);
    for (byte i = 0; i < 21; i++) {
      if (received == ReceiveCode[i]) {
        if (i >= 12 && i <= 18) {
          state[i - 12] = !state[i - 12];
          digitalWrite(sw_pins[i - 12], state[i - 12]);
          send_feedback(i - 12);
        }

        // else if (i == 0) security = !security;

        ir_timer = millis();
        ir_flag = 1;
        break;
      }
    }
  }

  if (ir_flag && millis() - ir_timer > 1000) {
    ir_flag = 0;
    IrReceiver.resume();
  }
}

void send_feedback(byte i) {

  switch (i) {
    case 0:
      sw1.updateAndReportParam("Power", state[i]);
      break;
    case 1:
      sw2.updateAndReportParam("Power", state[i]);
      break;
    case 2:
      sw3.updateAndReportParam("Power", state[i]);
      break;
    case 3:
      sw4.updateAndReportParam("Power", state[i]);
      break;
    case 4:
      sw5.updateAndReportParam("Power", state[i]);
      break;
    case 5:
      sw6.updateAndReportParam("Power", state[i]);
      break;
    case 6:
      sw7.updateAndReportParam("Power", state[i]);
      break;
  }
}