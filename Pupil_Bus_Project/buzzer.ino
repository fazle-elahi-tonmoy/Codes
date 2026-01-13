void beep(byte c, byte t){
  for(byte i=0; i<c; i++){
    digitalWrite(buzzer, 1);
    delay(t*100);
    digitalWrite(buzzer, 0);
    delay(t*100);
  }
}
