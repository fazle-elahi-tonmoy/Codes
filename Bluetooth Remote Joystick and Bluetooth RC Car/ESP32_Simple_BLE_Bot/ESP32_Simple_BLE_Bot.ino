#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Servo base, top;
BluetoothSerial SerialBT;


int lms = 32, lmf = 33, lmb = 25, rmf = 27, rmb = 26, rms = 13;
int speed = 100;
char x;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Bluetooth Car");
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);
  ledcAttachPin(lms, 0);
  ledcAttachPin(rms, 0);
  motor(0, 0);
}

void loop() {
  if (SerialBT.available()) {
    x = SerialBT.read();
    Serial.println(x);
    motor_mode();
  }
}
