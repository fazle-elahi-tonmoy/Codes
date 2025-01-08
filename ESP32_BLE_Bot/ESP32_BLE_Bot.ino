#include <BluetoothSerial.h>
#include <ESP32Servo.h>

Servo base, top;
BluetoothSerial SerialBT;


int lms = 32, lmf = 33, lmb = 25, rmf = 26, rmb = 27, rms = 13;
int speed = 150;
char x;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Rover");
  base.attach(22);
  top.attach(23);
  base.write(90);
  top.write(90);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  ledcSetup(14, 1000, 8);
  ledcSetup(15, 1000, 8);
  ledcAttachPin(lms, 14);
  ledcAttachPin(rms, 15);
  motor(0, 0);
}

void loop() {
  if (SerialBT.available()) {
    x = SerialBT.read();
    Serial.println(x);
    motor_mode();
  }
}
