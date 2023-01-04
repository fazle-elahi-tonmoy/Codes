void showing() {
  for (int i = 0; i < 7 ; i++) {
    for (int j = 0; j < 20; j++)
      (disp[i][j] == 1) ? digitalWrite(j + 22, LOW) : digitalWrite(j + 22, HIGH);
    digitalWrite(50 - i, HIGH);
    delayMicroseconds(100);
    digitalWrite(50 - i, LOW);
  }
}

void clearscr() {
  for (int i = 0; i < 7 ; i++)
    for (int j = 0; j < 20; j++) disp[i][j] = 0 ;
  for (int i = 44; i <= 50 ; i++) digitalWrite(i, LOW);
}
