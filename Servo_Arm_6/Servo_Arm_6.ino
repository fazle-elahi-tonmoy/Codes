#include "HCPCA9685.h"
HCPCA9685 HCPCA9685(0x40);

#define base_rest 250
#define shoulder_rest 300
#define elbow_rest 100
#define wrist_rest 250
#define grabber_rest 100

#define increament 1

byte b = 0, s = 0, e = 0, w = 0;
uint32_t mb, ms, me, mw;

int base = base_rest;
int shoulder = shoulder_rest;
int elbow = elbow_rest;
int wrist = wrist_rest;




void setup() {
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);  // Initialise default communication rate of the Bluetooth module
  HCPCA9685.Servo(0, base_rest);
  HCPCA9685.Servo(1, shoulder_rest);
  HCPCA9685.Servo(2, shoulder_rest);
  HCPCA9685.Servo(3, elbow_rest);
  HCPCA9685.Servo(4, wrist_rest);
  HCPCA9685.Servo(5, grabber_rest);
}

void loop() {
  move();
  if (Serial.available()) {
    char x = Serial.read();
    Serial.println(x);
    if (x == 'L') b = 1;
    else if (x == 'R') b = 2;
    else if (x == 'F') s = 2;
    else if (x == 'B') s = 1;
    else if (x == 'G') {
      b = 2;
      s = 2;
    } else if (x == 'I') {
      b = 1;
      s = 2;
    } else if (x == 'J') {
      b = 1;
      s = 1;
    } else if (x == 'H') {
      b = 2;
      s = 1;
    } else if (x == 'W') e = 2;
    else if (x == 'w') e = 0;
    else if (x == 'U') e = 1;
    else if (x == 'u') e = 0;
    else if (x == 'V') w = 1;
    else if (x == 'v') w = 0;
    else if (x == 'X') w = 2;
    else if (x == 'x') w = 0;

    else if (x >= '0' && x <= '9') {
      int p = x - '0';
      p = map(p, 0, 9, 100, 250);

      HCPCA9685.Servo(5, p);
    } else if (x == 'S') b = s = e = w = 0;
    else if (x == 'D') {
      HCPCA9685.Servo(0, base_rest);
      HCPCA9685.Servo(1, shoulder_rest);
      HCPCA9685.Servo(2, shoulder_rest);
      HCPCA9685.Servo(3, elbow_rest);
      HCPCA9685.Servo(4, wrist_rest);
      HCPCA9685.Servo(5, grabber_rest);
      base = base_rest;
      shoulder = shoulder_rest;
      elbow = elbow_rest;
      wrist = wrist_rest;
    }
  }
}
