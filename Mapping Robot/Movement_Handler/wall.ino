void wall_follow() {
  read_distance();
  if (front < 20) turn('L');
  error = (wall_mid - right) * 5;
  l_motor = l_base - error;
  r_motor = r_base + error;
  motor(l_motor, r_motor);
}
