void IR_Control() {
  int received = 0;
  if (IrReceiver.decode() && !ir_flag) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) IrReceiver.resume();
    else received = IrReceiver.decodedIRData.command;
    for (byte i = 0; i < 21; i++) {
      if (received == ReceiveCode[i]) {
        if (i >= 6 && i < 21) {
          state[i - 6] = !state[i - 6];
          send_feedback(i - 6);
        }

        else if (i == 0) {
          for (byte i = 0; i < 15; i++) (power) ? state[i] = 0 : state[i] = 1;
          power = !power;
        }

        else if (i == 2) security = !security;
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
      bulb1.updateAndReportParam("Power", state[i]);
      break;
    case 1:
      bulb2.updateAndReportParam("Power", state[i]);
      break;
    case 2:
      bulb3.updateAndReportParam("Power", state[i]);
      break;
    case 3:
      bulb4.updateAndReportParam("Power", state[i]);
      break;
    case 4:
      bulb5.updateAndReportParam("Power", state[i]);
      break;
    case 5:
      bulb6.updateAndReportParam("Power", state[i]);
      break;
    case 6:
      bulb7.updateAndReportParam("Power", state[i]);
      break;
    case 7:
      fan1.updateAndReportParam("Power", state[i]);
      break;
    case 8:
      fan2.updateAndReportParam("Power", state[i]);
      break;
    case 9:
      fan3.updateAndReportParam("Power", state[i]);
      break;
    case 10:
      fan4.updateAndReportParam("Power", state[i]);
      break;
    case 11:
      sw1.updateAndReportParam("Power", state[i]);
      break;
    case 12:
      sw2.updateAndReportParam("Power", state[i]);
      break;
    case 13:
      sw3.updateAndReportParam("Power", state[i]);
      break;
    case 14:
      sw4.updateAndReportParam("Power", state[i]);
      break;
  }
}