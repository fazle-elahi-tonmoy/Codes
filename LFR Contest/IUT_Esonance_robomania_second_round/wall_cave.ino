void wall_cave() {
  digitalWrite(13, HIGH);
  while (sum == 0){
    check();
    sl = sonarl.ping_cm();
    if (sl >=2 && sl <= 7) motorSpeed(0, 100);
    else if (sl >= 9 && sl <= 15) motorSpeed(100, 0);
    else motorSpeed(120, 120);
  }
  digitalWrite(13, LOW);
  counter=1;
}
