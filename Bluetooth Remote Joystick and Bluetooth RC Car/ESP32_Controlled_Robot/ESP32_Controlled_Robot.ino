#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define rmf 17
#define rmb 16
#define lmf 21
#define lmb 23

bool mode = 0;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("BRC 2");
  motor(0, 0);
  remote_control();
}

void loop() {
}
