byte servo1_update(byte a) {
  if (a == 1) {
    if (servo1_stat == servo1_pos[0]) return a + 1;
    if(servo1_left_rotation_speed == 0) return 8;
    if (millis() - ms1 > (100 - servo1_left_rotation_speed)) {
      ms1 = millis(); servo1_stat++; servo1.write(servo1_stat);
    }
  }
  else if (a == 2) {
    if (millis() - ms1 > servo1_left_waiting_time * 1000) return a + 1;
  }
  else if (a == 3) {
    if (servo1_stat == servo1_pos[1]) return a + 1;
    if(servo1_left_to_mid_rotation_speed == 0) return 8;
    if (millis() - ms1 > (100 - servo1_left_to_mid_rotation_speed)) {
      ms1 = millis(); servo1_stat--; servo1.write(servo1_stat);
    }
  }
  else if (a == 4) {
    if (millis() - ms1 > servo1_mid_waiting_time * 1000) return a + 1;
  }
  else if (a == 5) {
    if (servo1_stat == servo1_pos[2]) return a + 1;
    if(servo1_right_rotation_speed == 0) return 8;
    if (millis() - ms1 > (100 - servo1_right_rotation_speed)) {
      ms1 = millis(); servo1_stat--; servo1.write(servo1_stat);
    }
  }
  else if (a == 6) {
    if (millis() - ms1 > servo1_right_waiting_time * 1000) return a + 1;
  }
  else if (a == 7) {
    if (servo1_stat == servo1_pos[1]) return a + 1;
    if(servo1_right_to_mid_rotation_speed == 0) return 8;
    if (millis() - ms1 > (100 - servo1_right_to_mid_rotation_speed)) {
      ms1 = millis(); servo1_stat++; servo1.write(servo1_stat);
    }
  }
  return a;
}

byte servo2_update(byte a) {
  if (a == 1) {
    if (servo2_stat == servo2_pos[0]) return a + 1;
    if(servo2_left_rotation_speed == 0) return 8;
    if (millis() - ms2 > (100 - servo2_left_rotation_speed)) {
      ms2 = millis(); servo2_stat++; servo2.write(servo2_stat);
    }
  }
  else if (a == 2) {
    if (millis() - ms2 > servo2_left_waiting_time * 1000) return a + 1;
  }
  else if (a == 3) {
    if (servo2_stat == servo2_pos[1]) return a + 1;
    if(servo2_left_to_mid_rotation_speed == 0) return 8;
    if (millis() - ms2 > (100 - servo2_left_to_mid_rotation_speed)) {
      ms2 = millis(); servo2_stat--; servo2.write(servo2_stat);
    }
  }
  else if (a == 4) {
    if (millis() - ms2 > servo2_mid_waiting_time * 1000) return a + 1;
  }
  else if (a == 5) {
    if (servo2_stat == servo2_pos[2]) return a + 1;
    if(servo2_right_rotation_speed == 0) return 8;
    if (millis() - ms2 > (100 - servo2_right_rotation_speed)) {
      ms2 = millis(); servo2_stat--; servo2.write(servo2_stat);
    }
  }
  else if (a == 6) {
    if (millis() - ms2 > servo2_right_waiting_time * 1000) return a + 1;
  }
  else if (a == 7) {
    if (servo2_stat == servo2_pos[1]) return a + 1;
    if(servo2_right_to_mid_rotation_speed == 0) return 8;
    if (millis() - ms2 > (100 - servo2_right_to_mid_rotation_speed)) {
      ms2 = millis(); servo2_stat++; servo2.write(servo2_stat);
    }
  }
  return a;
}
