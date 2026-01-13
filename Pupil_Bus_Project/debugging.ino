void debug_display(){
  SerialBT.print(String(gps.satellites.value()) + " ");
  SerialBT.print(gps.location.lat(), 5);
  SerialBT.print(' ');
  SerialBT.print(gps.location.lng(), 5);
  SerialBT.print(' ');
  SerialBT.println(gps.speed.kmph(),2);
}