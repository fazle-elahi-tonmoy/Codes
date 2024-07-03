#include <ESP32Servo.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define lmf1 13
#define lmf2 12
#define lmb1 4
#define lmb2 2
#define rmf1 16
#define rmf2 17
#define rmb1 14
#define rmb2 27

#define grab 60
#define drop 120
#define rise 10
#define mrise 100
#define lower 140
Servo hand;
Servo lift;

bool mode = 0;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("BRC");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  hand.setPeriodHertz(50);
  lift.setPeriodHertz(50);
  hand.attach(23, 500, 2500);
  lift.attach(22, 500, 2500);
  hand.write(drop);
  lift.write(rise);
  ledcSetup(2, 1000, 8);
  ledcAttachPin(15, 2);
  ledcWrite(2, 255);

  pinMode(lmf1, OUTPUT);
  pinMode(lmb1, OUTPUT);
  pinMode(rmf1, OUTPUT);
  pinMode(rmb1, OUTPUT);
  pinMode(lmf2, OUTPUT);
  pinMode(lmb2, OUTPUT);
  pinMode(rmf2, OUTPUT);
  pinMode(rmb2, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(33, 0);
  digitalWrite(32, 0);
  motor(0, 0);
  remote_control();
}

void loop() {
}
