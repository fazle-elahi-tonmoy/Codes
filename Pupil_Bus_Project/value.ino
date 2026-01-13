String floatToString(float value, int precision) {
  char buffer[20];
  dtostrf(value, 0, precision, buffer);
  return String(buffer);
}