byte servo1_update(byte a) {
  if (a % 2 == 0) {
    if (millis() - ms1 > servo1_wait * 1000) return a + 1;
  }
  else if (a == 1) {
    if (servo1_stat == servo1_pos[0]) return a + 1;
    if (millis() - ms1 > (100 - servo1_speed)) {
      ms1 = millis();
      (servo1_act[0]) ? servo1_stat-- : servo1_stat++;
      servo1.write(servo1_stat);
    }
  }
  else if (a == 3) {
    if (servo1_stat == servo1_pos[1]) return a + 1;
    if (millis() - ms1 > (100 - servo1_speed)) {
      ms1 = millis();
      (servo1_act[0]) ? servo1_stat++ : servo1_stat--;
      servo1.write(servo1_stat);
    }
  }
  else if (a == 5) {
    if (servo1_stat == servo1_pos[2]) return a + 1;
    if (millis() - ms1 > (100 - servo1_speed)) {
      ms1 = millis();
      (servo1_act[1]) ? servo1_stat-- : servo1_stat++;
      servo1.write(servo1_stat);
    }
  }
  else if (a == 7) {
    if (servo1_stat == servo1_pos[1]) return a + 1;
    if (millis() - ms1 > (100 - servo1_speed)) {
      ms1 = millis();
      (servo1_act[1]) ? servo1_stat++ : servo1_stat--;
      servo1.write(servo1_stat);
    }
  }
  return a;
}

byte servo2_update(byte a) {
  if (a % 2 == 0) {
    if (millis() - ms2 > servo2_wait * 1000) return a + 1;
  }
  else if (a == 1) {
    if (servo2_stat == servo2_pos[0]) return a + 1;
    if (millis() - ms2 > (100 - servo2_speed)) {
      ms2 = millis();
      (servo2_act[0]) ? servo2_stat-- : servo2_stat++;
      servo2.write(servo2_stat);
    }
  }
  else if (a == 3) {
    if (servo2_stat == servo2_pos[1]) return a + 1;
    if (millis() - ms2 > (100 - servo2_speed)) {
      ms2 = millis();
      (servo2_act[0]) ? servo2_stat++ : servo2_stat--;
      servo2.write(servo2_stat);
    }
  }
  else if (a == 5) {
    if (servo2_stat == servo2_pos[2]) return a + 1;
    if (millis() - ms2 > (100 - servo2_speed)) {
      ms2 = millis();
      (servo2_act[1]) ? servo2_stat-- : servo2_stat++;
      servo2.write(servo2_stat);
    }
  }
  else if (a == 7) {
    if (servo2_stat == servo2_pos[1]) return a + 1;
    if (millis() - ms2 > (100 - servo2_speed)) {
      ms2 = millis();
      (servo2_act[1]) ? servo2_stat++ : servo2_stat--;
      servo2.write(servo2_stat);
    }
  }
  return a;
}
