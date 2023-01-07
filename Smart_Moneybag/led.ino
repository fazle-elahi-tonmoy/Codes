void blink(byte a){
  for(byte i = 0; i<a; i++){
    digitalWrite(LED, 1); delay(100);
    digitalWrite(LED, 0); delay(100);
  }
}