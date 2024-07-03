void Relay_Control() {
  bool flag = 0;
  for (byte i = 0; i < 15; i++) {
    if (state[i]) flag = 1;
    if (i >= 0 && i < 7) digitalWrite(bulb_pins[i], state[i]);
    else if (i >= 7 && i < 11) digitalWrite(fan_pins[i - 7], state[i]);
    else if (i >= 11 && i < 15) digitalWrite(switch_pins[i - 11], state[i]);
  }
  power = flag;
}