void speed_control(){
  int v = map(analogRead(7), 0, 1020, 0, 20);
  v = v - 10;
  (v < 0) ? spdr = spd + v : spdr = spd;
  (v > 0) ? spdl = spd - v : spdl = spd;
}
