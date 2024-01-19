#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define lx 33
#define ly 32
#define lb 16
#define rx 35
#define ry 34
#define rb 23
#define pl 39
#define pr 36
#define l1 4
#define l2 15
#define r1 18
#define r2 19
#define e1 16
#define e2 23
#define calb 0
#define led 12

const int button[7] = { lb, rb, l1, l2, r1, r2, calb };
const int pot[6] = { lx, ly, rx, ry, pl, pr };
int pot_val[6], pot_min[2] = { 0, 0 }, pot_max[2] = { 4095, 4095 };
int pot_mid[4] = { 2000, 1980, 1950, 1960 };
int button_val[6];
int temp[12] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };


void setup() {
  for (byte i = 0; i < 7; i++) pinMode(button[i], INPUT_PULLUP);
  Serial.begin(4800);
}

void loop() {
  byte x = press(calb);
  if (x) {
    Serial.println(x);
    if (x == 1) send_data();

    else if (x == 2) {
      while (!press(calb)) {
        for (byte i = 0; i < 7; i++) Serial.printf("%d ", digitalRead(button[i]));
        for (byte i = 0; i < 6; i++) Serial.printf("%d ", analogRead(pot[i]));
        Serial.println();
      }
    }

    else if (x == 3) {
      while (!press(calb)) {
        joystick();
        for (byte i = 0; i < 6; i++) Serial.printf("%d ", button_val[i]);
        for (byte i = 0; i < 6; i++) Serial.printf("%d ", pot_val[i]);
        Serial.println();
      }
    }

    else if (x == 4) {
      while (!press(calb)) {
        int p = recheck();
        if (p){
          digitalWrite(led, 1);
          delay(100);
          digitalWrite(led, 0);
          // Serial.println(p,BIN);
        } 
      }
    }
  }
}
