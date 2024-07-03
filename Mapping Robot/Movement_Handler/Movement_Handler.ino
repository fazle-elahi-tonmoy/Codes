#include <BleKeyboard.h>
#include "Adafruit_VL53L0X.h"
BleKeyboard bleKeyboard("Mapping Robot");
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define SHT_LOX1 33
#define SHT_LOX2 32


VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

int front = 0, right = 0;
uint32_t k_timer, w_timer, n_timer;
int x = 0, y = 0, nav = 1;
byte motor_pin[4] = { 05, 18, 16, 17 };
int l_base = 95, r_base = 80, error = 0, wall_mid = 12, l_motor, r_motor, last_error = 0;
bool scan = 0, inc = 0, start = 0, trigger = 0;

void gotTouchEvent() {
  start = 0;
  Serial1.write('I');
  trigger = 1;
}

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  for (byte i = 0; i < 4; i++) pinMode(motor_pin[i], OUTPUT);
  ledcSetup(10, 1000, 8);
  ledcSetup(11, 1000, 8);
  ledcAttachPin(19, 10);
  ledcAttachPin(4, 11);
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 25, 26);
  touchAttachInterrupt(T3, gotTouchEvent, 40);
  setID();
  bleKeyboard.begin();
  delay(100);
  k_timer = w_timer = n_timer = millis();
  motor(0, 0);
  lox1.startRangeContinuous(1);
  lox2.startRangeContinuous(1);
}

void loop() {
  int r = push(0);
  if (r) {
    if (r == 1) {
      start = 1;
      Serial1.write('F');
      delay(1000);
      k_timer = n_timer = millis();
    }
    if (r == 2) {
      Serial1.write('S');
      delay(5000);
      incoming();
    }
    if (r == 3) {
      while (1) {
        read_distance();
        Serial.printf("%d %d\n", front, right);
      }
    }
    if (r == 4)
      while (1) data_entry();
    if (r == 5) motor(l_base, r_base);
    if (r == 6) turn('L');
  }

  if (start) {
    data_entry();
    navigation();
    if (trigger) {
      start = 0;
      motor(0, 0);
    }
  }


  read_distance();
  (wall_mid == right) ? digitalWrite(2, 1) : digitalWrite(2, 0);
}
