#include "BluetoothSerial.h"
#include <ESP32Servo.h>
Servo steering;
BluetoothSerial SerialBT;
int st_mid = 80, st_left = 60, st_right = 100;

#define mf 21
#define mb 22
#define ms 23

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Toy Car");
  steering.attach(13);
  steering.write(st_mid);
  ledcSetup(10, 1000, 8);
  ledcAttachPin(ms, 10);
  ledcWrite(10, 100);
  pinMode(mf, OUTPUT);
  pinMode(mb, OUTPUT);
  remote_control();
}

void loop() {
}
