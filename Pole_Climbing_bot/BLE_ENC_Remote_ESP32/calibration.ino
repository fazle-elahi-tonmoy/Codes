void cal() {
  for (byte i = 0; i < 4; i++) {
    joy_max[i] = 0;
    joy_min[i] = 4095;
  }

  while (!push(r1)) {
    for (byte i = 0; i < 4; i++) {
      joystick[i] = analogRead(joystick_pin[i]);
      joy_max[i] = max(joy_max[i],joystick[i]);
      joy_min[i] = min(joy_min[i],joystick[i]);
    }
  }

  for (byte i = 0; i < 4; i++) {
    joy_max[i] -= 50;
    joy_min[i] += 50;
    joy_mid[i] = ((joy_max[i] + joy_min[i]) / 2) - 100;
    EEPROM.write(i, joy_mid[i] / 16);
    EEPROM.write(i+4, joy_min[i] / 16);
    EEPROM.write(i+8, joy_max[i] / 16);
  }
  EEPROM.commit();
}
