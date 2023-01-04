#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire oled;
String value;
int s[6];
int mpin[6] = { 3, 4, 5, 7, 8, 11 };                //defining the motor driver pins
bool motor_A_direction = 0, motor_B_direction = 0;  //change the value into 1 for opposite direction

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  pin_define();  //direction setting
  for (byte i = 0; i < 6; i++) pinMode(mpin[i], OUTPUT);
  motor(100, 100);
  // analog_display();
  TechTopia();
}
void loop() {
}

void pin_define() {
  (motor_A_direction) ? mpin[1] = 5 : mpin[1] = 4;
  (motor_A_direction) ? mpin[2] = 4 : mpin[2] = 5;
  (motor_B_direction) ? mpin[3] = 7 : mpin[3] = 8;
  (motor_B_direction) ? mpin[4] = 8 : mpin[4] = 7;
}
void motor(int a, int b) {
  if (a >= 0) {
    digitalWrite(mpin[1], 1);
    digitalWrite(mpin[2], 0);
  } else {
    a = -a;
    digitalWrite(mpin[1], 0);
    digitalWrite(mpin[2], 1);
  }
  if (b >= 0) {
    digitalWrite(mpin[3], 1);
    digitalWrite(mpin[4], 0);
  } else {
    b = -b;
    digitalWrite(mpin[3], 0);
    digitalWrite(mpin[4], 1);
  }
  analogWrite(mpin[0], a);
  analogWrite(mpin[5], b);
}
