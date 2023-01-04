void servo_move() {
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc.setRow(0, 3, 0xFF); lc.setRow(0, 4, 0xFF);
  lc.setRow(1, 3, 0xFF); lc.setRow(1, 4, 0xFF); // middle position indicating display
  delay(500);
  byte t1_phase; servo1_stat = servo1_pos[1]; servo2_stat = servo2_pos[1];
  s1_phase = s2_phase = 1;
  while (1) {
    if (t1_phase != s1_phase) {
      t1_phase = s1_phase; stat(t1_phase);
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
}
