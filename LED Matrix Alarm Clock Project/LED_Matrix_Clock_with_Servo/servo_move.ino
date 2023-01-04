void servo_move() {
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo1.write(servo1_pos[1]); //Servo 1 middle position
  servo2.write(servo2_pos[1]); //Servo 2 middle position
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc.setRow(0, 3, 0xFF); lc.setRow(0, 4, 0xFF);
  lc.setRow(1, 3, 0xFF); lc.setRow(1, 4, 0xFF); // middle position indicating display
  delay(500);
  byte t1_phase, t2_phase; servo1_stat = servo1_pos[1]; servo2_stat = servo2_pos[1];
  s1_phase = s2_phase = 1;
  (servo1_pos[1] > servo1_pos[0]) ? servo1_act[0] = 1 : servo1_act[0] = 0;
  (servo1_pos[1] > servo1_pos[2]) ? servo1_act[1] = 1 : servo1_act[1] = 0;
  (servo2_pos[1] > servo2_pos[0]) ? servo2_act[0] = 1 : servo2_act[0] = 0;
  (servo2_pos[1] > servo2_pos[2]) ? servo2_act[1] = 1 : servo2_act[1] = 0;
  while (1) {
    if (t1_phase != s1_phase) {
      t1_phase = s1_phase; stat(t1_phase);
      servo1_speed_update(t1_phase);
      if (!servo1_speed) s1_phase = 8;
    }
    if (t2_phase != s2_phase) {
      t2_phase = s2_phase;
      servo2_speed_update(t2_phase);
      if (!servo2_speed) s1_phase = 8;
    }
    s1_phase = servo1_update(s1_phase);
    s2_phase = servo2_update(s2_phase);
    if (s1_phase >= 8 && s2_phase >= 8) break;
  }

  for (int i = 3; i >= 0; i--) { //horizontal line expanding animation
    lc.clearDisplay(0); lc.clearDisplay(1);
    lc.setRow(0, i, 0xFF); lc.setRow(1, i, 0xFF);
    lc.setRow(0, 7 - i, 0xFF); lc.setRow(1, 7 - i, 0xFF);
    delay(150);
  }
  delay(3000); //wait for 3 second here
  for (int i = 0; i <= 3; i++) { //horizontal line shrinking animation
    lc.clearDisplay(0); lc.clearDisplay(1);
    lc.setRow(0, i, 0xFF); lc.setRow(1, i, 0xFF);
    lc.setRow(0, 7 - i, 0xFF); lc.setRow(1, 7 - i, 0xFF);
    delay(150);
  }
  delay(1000); //wait for a bit here to show the final screen
  servo1.detach();
  servo2.detach();
}
