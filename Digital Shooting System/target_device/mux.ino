int mux1_check(byte x) {
  for (int i = 0; i < 4; i++) {
    byte value = x & (1 << i);
    value = value >> i;
    digitalWrite(mux_pin1[i], value);
  }
  int val = analogRead(6);
  return val;
}

int mux2_check(byte x) {
  for (int i = 0; i < 4; i++) {
    byte value = x & (1 << i);
    value = value >> i;
    digitalWrite(mux_pin2[i], value);
  }
  int val = analogRead(7);
  return val;
}