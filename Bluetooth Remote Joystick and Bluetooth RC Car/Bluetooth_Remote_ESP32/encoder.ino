byte Lencoder_read() {
  Lposition = Lencoder.getCount();
  byte state = 0;
  if (lastPosL != Lposition) {
    (lastPosL > Lposition) ? state = 2 : state = 1;
    lastPosL = Lposition;
    Lencoder.pauseCount();
    delay(100);
    Lencoder.resumeCount();

  }
  return state;
}

byte Rencoder_read() {
  Rposition = Rencoder.getCount();
  byte state = 0;
  if (lastPosR != Rposition) {
    (lastPosR > Rposition) ? state = 2 : state = 1;
    lastPosR = Rposition;
    Rencoder.pauseCount();
    delay(100);
    Rencoder.resumeCount();
  }
  return state;
}