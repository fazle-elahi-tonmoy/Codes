void Serial_Test() {
  if (Serial.available()) {
    char x = Serial.read();
    if (x == 'a') show_analog_value();
    if (x == 'd') show_digital_value();
    if (x == 's')
      while (1) {
        sonar_read();
        Serial.println(distance);
      }
    if (x == 'f') {
      motor(200, 200);
      delay(3000);
      motor(0, 0);
    }

    if (x == 'l') {
      motor(-200, 200);
      delay(3000);
      motor(0, 0);
    }

    if (x == 'r') {
      motor(200, -200);
      delay(3000);
      motor(0, 0);
    }

    if (x == 'x') {
      while (1) {
        reading();
        Serial.println(String(ss[0]) + " " + String(ss[1]));
      }
    }
  }
}