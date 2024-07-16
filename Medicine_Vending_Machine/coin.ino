bool coin_detect() {
  if (analogRead(A6) > 900) return 0;
  else return 1;
}