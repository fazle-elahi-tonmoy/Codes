#include "BluetoothSerial.h"
#include <ESP32Servo.h>
BluetoothSerial SerialBT;

#define lmf 16
#define lmb 0
#define rmf 4
#define rmb 17
#define lms 15
#define rms 2
#define sw 19
#define led1 14
#define led2 32

#define grabl 110
#define dropl 0
#define grabr 50
#define dropr 160
#define rise 150
#define lower 10
Servo handl;
Servo handr;
Servo lift;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("BRC");
  servo_initiate();
  motor_initiate();
  bluetooth();
}

void loop() {
}
