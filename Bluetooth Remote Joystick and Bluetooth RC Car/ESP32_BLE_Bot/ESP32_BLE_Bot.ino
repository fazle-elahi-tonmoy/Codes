#include <BluetoothSerial.h>
BluetoothSerial SerialBT;


int lms = 32, lmf = 25, lmb = 33, rmf = 27, rmb = 26, rms = 14;
int speed = 255;
char x;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Defender");
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);
  ledcAttachPin(lms, 0);
  ledcAttachPin(rms, 1);
  motor(0, 0);
}

void loop() {
  if (SerialBT.available()) {
    x = SerialBT.read();
    Serial.println(x);
    motor_mode();
  }

  delay(10);
}
