void move() {
  if (b == 1 && base > 10 && millis() - mb > 10) {
    base += increament;
    HCPCA9685.Servo(0, base);
    mb = millis();
  }
  if (b == 2 && base < 450 && millis() - mb > 10) {
    base -= increament;
    HCPCA9685.Servo(0, base);
    mb = millis();
  }

  if (s == 2 && shoulder > 10 && millis() - ms > 50) {
    shoulder += increament;
    HCPCA9685.Servo(1, shoulder);
    HCPCA9685.Servo(2, shoulder);
    ms = millis();
  }
  if (s == 1 && shoulder < 450 && millis() - ms > 50) {
    shoulder -= increament;
    HCPCA9685.Servo(1, shoulder);
    HCPCA9685.Servo(2, shoulder);
    ms = millis();
  }


  if (e == 1 && elbow > 10 && millis() - me > 50) {
    elbow += increament;
    HCPCA9685.Servo(3, elbow);
    me = millis();
  }
  if (e == 2 && elbow < 450 && millis() - me > 50) {
    elbow -= increament;
    HCPCA9685.Servo(3, elbow);
    me = millis();
  }

  if (w == 1 && wrist > 10 && millis() - mw > 50) {
    wrist += increament;
    HCPCA9685.Servo(4, wrist);
    mw = millis();
  }
  if (w == 2 && wrist < 450 && millis() - mw > 50) {
    wrist -= increament;
    HCPCA9685.Servo(4, wrist);
    mw = millis();
  }
}