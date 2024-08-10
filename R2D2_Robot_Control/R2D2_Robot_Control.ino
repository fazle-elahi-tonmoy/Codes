#include "BluetoothSerial.h"
#include <ESP32Servo.h>
BluetoothSerial SerialBT;
Servo head;

#define speakerPin 19
#define rmf 14
#define rmb 12
#define lmf 25
#define lmb 26

bool idle = 0;

void setup() {
  SerialBT.begin("BRC 5");
  pinMode(speakerPin, OUTPUT);
  randomSeed(analogRead(32) / 4);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWrite(27, 1);
  head.attach(15);
  head.write(100);

  ledcSetup(15, 1000, 8);
  ledcAttachPin(13, 15);
  ledcAttachPin(33, 15);
  ledcWrite(15, 250);
  ledcSetup(10, 1000, 8);
}

void loop() {
  remote_control();
  if (idle) sound(2000);
}

void sound(int K) {
  for (int i = 0; i <= random(3, 9); i++) {
    if (SerialBT.available()) break;
    int frequency = K + random(-1700, K);
    ledcSetup(10, frequency, 8);
    ledcAttachPin(speakerPin, 10);
    ledcWriteTone(10, frequency);
    delay(random(70, 170));
    ledcWriteTone(10, 0);
    delay(random(0, 30));
  }
  idle = 0;
}
