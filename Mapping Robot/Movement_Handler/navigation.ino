void navigation() {
  if (millis() - n_timer > 500) {
    n_timer = millis();
    if (nav == 1) x++;
    else if (nav == 2) y++;
    else if (nav == 3) x--;
    else if (nav == 4) y--;
  }
  wall_follow();
}

void turn(char x) {
  (x == 'L') ? nav++ : nav--;
  if (nav > 4) nav = 1;
  if (nav == 0) nav = 4;
  motor(0, 0);
  delay(1000);
  (x == 'L') ? motor(-100, 100) : motor(100, -100);
  delay(500);
  (x == 'R') ? motor(-100, 100) : motor(100, -100);
  delay(50);
  motor(0, 0);
  for (int i = 0; i < 1000; i++) {
    read_distance();
  }
  k_timer = n_timer = millis();
}