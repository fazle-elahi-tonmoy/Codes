void gps_read() {
  if (gpsSerial.available()) {
    while (gpsSerial.available())
      gps.encode(gpsSerial.read());
    lat = gps.location.lat();
    lng = gps.location.lng();
    latitude = floatToString(lat, 5);
    longitude = floatToString(lng, 5);
    // Serial.println(latitude + ", " + longitude);
    (!gps.satellites.value()) ? gps_connected = 0 : gps_connected = 1;
  }
}
