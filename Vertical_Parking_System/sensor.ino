bool sensor_read(byte a, bool trigger) {
  
  if (trigger && digitalRead(a)) {
    delay(50);
    if (digitalRead(a)) return 0;
  } 
  
  else if (!trigger && !digitalRead(a)) {
    delay(50);
    if (!digitalRead(a)) return 0;
  }
  return 1;
}