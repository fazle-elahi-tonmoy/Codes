#include <ESP32Servo.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

Servo grabber;
Servo arm_2;
Servo arm_1;
Servo base;

bool armMode = 0;

int rmf = 26, rmb = 25, lmf = 14, lmb = 27, lms = 13, rms = 12;
int grab_pos = 90, arm1_pos = 160, arm2_pos = 10, base_pos = 80;
int arm1_dir = 0, arm2_dir = 0, base_dir = 0;
int speed = 255;
char x;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ADV ROVER");
  grabber.attach(16);
  grabber.write(grab_pos);
  arm_2.attach(4);
  arm_2.write(arm2_pos);
  arm_1.attach(2);
  arm_1.write(arm1_pos);
  base.attach(15);
  base.write(base_pos);

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
    
    if (x == 'w') armMode = 0;
    else if (x == 'W') armMode = 1;

    if (armMode) arm_mode();
    else motor_mode();
  }

  if (arm1_dir) {
    arm1_pos += arm1_dir;
    if (arm1_pos > 180) arm1_pos = 180;
    if (arm1_pos < 0) arm1_pos = 0;
    arm_1.write(arm1_pos);
  }

  if (arm2_dir) {
    arm2_pos += arm2_dir;
    if (arm2_pos > 180) arm2_pos = 180;
    if (arm2_pos < 0) arm2_pos = 0;
    arm_2.write(arm2_pos);
  }

  if (base_dir) {
    base_pos += base_dir;
    if (base_pos > 180) base_pos = 180;
    if (base_pos < 0) base_pos = 0;
    base.write(base_pos);
  }

  if (arm1_dir || arm2_dir || base_dir) delay(10);
}
