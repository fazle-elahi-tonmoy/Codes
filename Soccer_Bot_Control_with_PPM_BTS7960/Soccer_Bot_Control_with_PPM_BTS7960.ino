#include "ppm.h"
int motor_pin[6] = { 5, 6, 7, 8, 9, 10 };
#define mid_val 1500
#define dead_zone 100
int spl = 13, spr = 13;
unsigned long previousMillis = 0;
int forward, sideways;
int lmotor, rmotor;
bool initial = 0;

void setup() {
  Serial.begin(115200);
  ppm.begin(12, false);
  for (int i = 1; i < 5; i++) pinMode(motor_pin[i], OUTPUT);
}

void loop() {
  short throttle = ppm.read_channel(3);
  short roll = ppm.read_channel(1);
  short swa = ppm.read_channel(5);

  if (abs(throttle - mid_val) < dead_zone) forward = 0;
  else forward = min(((abs(throttle - mid_val) - dead_zone) / 35), 10) * ((throttle - mid_val > 0) - (throttle - mid_val < 0));
  if (abs(roll - mid_val) < dead_zone) sideways = 0;
  else sideways = min(((abs(roll - mid_val) - dead_zone) / 35), 10) * ((roll - mid_val > 0) - (roll - mid_val < 0));
  if (forward == 0 && sideways == 0) initial = 1;
  if (initial) {
    (forward >= 0) ? lmotor = forward + sideways : lmotor = forward - sideways;
    (forward >= 0) ? rmotor = forward - sideways : rmotor = forward + sideways;
    if (lmotor > 10) lmotor = 10;
    if (lmotor < -10) lmotor = -10;
    if (rmotor > 10) rmotor = 10;
    if (rmotor < -10) rmotor = -10;
    (swa > 1500) ? motor(lmotor * spl, rmotor * spr) : motor(lmotor * (spl + 12), rmotor * (spr + 12));
  }
}

void motor(int a, int b) {
  digitalWrite(motor_pin[1], (a > 0));
  digitalWrite(motor_pin[2], (a < 0));
  digitalWrite(motor_pin[3], (b > 0));
  digitalWrite(motor_pin[4], (b < 0));
  analogWrite(motor_pin[0], abs(a));
  analogWrite(motor_pin[5], abs(b));
  Serial.println(String(a) + " " + String(b));
}
