#include "BluetoothSerial.h"
#include <ESP32Servo.h>
Servo servo;
BluetoothSerial SerialBT;

byte motor_pin[4] = { 22, 5, 26, 25 };
const int relay = 13;
void setup() {
  Serial.begin(115200);
  servo.attach(15);
  ledcSetup(10, 1000, 8);
  ledcSetup(11, 1000, 8);
  ledcAttachPin(17, 10);
  ledcAttachPin(23, 11);
  for (byte i = 0; i < 4; i++) pinMode(motor_pin[i], OUTPUT);
  pinMode(relay, OUTPUT);
  remote_control();
}

void loop() {
  // put your main code here, to run repeatedly:
}
