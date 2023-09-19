#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include <BleKeyboard.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "flappy.h"
#include "space.h"
#include"dx_ball.h"
#include "JRCBoard_logo.h"
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
BleKeyboard bleKeyboard("BLE Controller");

#define SW 26
#define up 19
#define down 0
#define indicator 13
bool ble_connection = 0;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(indicator, OUTPUT);
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.invertDisplay(true);
  oled.drawBitmap(0, 0, JRC_Logo, 128, 64, 1);
  oled.display();
  // bleKeyboard.begin();
  // digitalWrite(indicator, 1);
}

void loop() {
  byte r = push(SW);
  if (r) {
    r = menu();
    if (r) {
      if (r == 1) presentation();
      else if (r == 2) media();
      else if (r == 3) stop_watch();
      else if (r == 4) flappy_bird();
      else if (r == 5) space_jam();
      else if (r == 6) DXBall();
      else if (r == 7) snake_game();
    }
    oled.clearDisplay();
    oled.invertDisplay(true);
    oled.drawBitmap(0, 0, JRC_Logo, 128, 64, 1);
    oled.display();
  }
}
