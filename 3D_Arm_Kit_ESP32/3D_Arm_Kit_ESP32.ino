#include "BluetoothSerial.h"
#include <ESP32Servo.h>
BluetoothSerial SerialBT;
Servo base, arm1, arm2, grab;
int grab_close = 30, grab_open = 100;
int arm2_extend = 60, arm2_close = 150;
int arm1_extend = 30, arm1_close = 160;
int base_r = 0, base_l = 180;

int grab_pos = grab_open, arm2_pos = arm2_close, arm1_pos = arm1_extend, base_pos = 90;
int arm2_dir = 0, arm1_dir = 0, base_dir = 0;

void setup() {
  arm1.attach(16);
  arm1.write(arm1_pos);
  delay(500);
  arm2.attach(5);
  arm2.write(arm2_pos);
  delay(500);
  base.attach(17);
  base.write(base_pos);
  delay(500);
  grab.attach(4);
  grab.write(grab_pos);
  delay(1000);
  Serial.begin(115200);
  SerialBT.begin("Robot Hand");
}

void loop() {
  bluetooth_command();

  manual_command();

  if (arm1_dir) {
    (arm1_dir == 1) ? arm1_pos-- : arm1_pos++;
    if (arm1_pos > arm1_close) {
      arm1_pos = arm1_close;
      arm1_dir = 0;
    }
    if (arm1_pos < arm1_extend) {
      arm1_pos = arm1_extend;
      arm1_dir = 0;
    }
    arm1.write(arm1_pos);
  }

  if (arm2_dir) {
    (arm2_dir == 1) ? arm2_pos-- : arm2_pos++;
    if (arm2_pos > arm2_close) {
      arm2_pos = arm2_close;
      arm2_dir = 0;
    }
    if (arm2_pos < arm2_extend) {
      arm2_pos = arm2_extend;
      arm2_dir = 0;
    }
    arm2.write(arm2_pos);
  }

  if (base_dir) {
    (base_dir == 1) ? base_pos-- : base_pos++;
    if (base_pos > base_l) {
      base_pos = base_l;
      base_dir = 0;
    }
    if (base_pos < base_r) {
      base_pos = base_r;
      base_dir = 0;
    }
    base.write(base_pos);
  }
  delay(20);
}
