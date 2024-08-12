#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"
#include <ESP32Encoder.h>
#include <EEPROM.h>
#include "bitmap.h"
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("BLE Joystick");
ESP32Encoder Lencoder;
ESP32Encoder Rencoder;
BluetoothSerial SerialBT;
Adafruit_SSD1306 display(128, 32, &Wire, -1);

long refresh_timer;

#define lx 33
#define ly 32
#define lb 25
#define rx 35
#define ry 34
#define rb 26
#define l1 4
#define l2 15
#define r1 18
#define r2 19
#define el 16
#define er 23
#define calb 0
#define FRAME_COUNT sizeof(frames) / sizeof(frames[0])
int frame = 0;
const int button[8] = { lb, rb, l1, l2, r1, r2, el, er };
const int joystick_pin[4] = { lx, ly, rx, ry };
int joystick[4], joy_max[4], joy_min[4], joy_mid[4];
int button_val[8];
int temp[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
long Lposition, Rposition, lastPosL, lastPosR;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.setTextColor(1);
  display.setTextSize(2);
  EEPROM.begin(32);
  for (byte i = 0; i < 4; i++) {
    joy_mid[i] = EEPROM.read(i) * 16;
    joy_min[i] = EEPROM.read(i + 2) * 16;
    joy_max[i] = EEPROM.read(i + 4) * 16;
  }
  for (byte i = 0; i < 8; i++) pinMode(button[i], INPUT_PULLUP);
  pinMode(calb, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  Lencoder.attachHalfQuad(17, 5);
  Rencoder.attachHalfQuad(13, 14);
}

void loop() {
  home_screen();
  if (push(calb)) {
    byte r = menu();
    if (r) {
      if (r == 1) send_data();
      if (r == 2) ble_joystick();
      if (r == 3) {
        display.clearDisplay();
        text("CALIBRATE", 11, 8);
        display.display();
        cal();
        display.clearDisplay();
        display.setTextSize(1);
        for (byte i = 0; i < 4; i++)
          text(String(joy_min[i]) + "    " + String(joy_mid[i]) + "    " + String(joy_max[i]), 4, i * 8);
        display.display();
        while (!push(calb))
          ;
        display.setTextSize(2);
      }
      if (r == 4) pot_display();
      if (r == 5) button_display();
      if (r == 6) console_display();
    }
  }
}
