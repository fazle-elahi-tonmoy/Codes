#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include "BluetoothSerial.h"
#include <ESP32Encoder.h>
#include <EEPROM.h>
#include "bitmap.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_bt.h"
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("Smart Joystick");
ESP32Encoder Lencoder;
ESP32Encoder Rencoder;
BluetoothSerial SerialBT;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

long refresh_timer;



#define lx 32
#define ly 35
#define lb 33
#define rx 39
#define ry 34
#define rb 19
#define l1 25
#define r1 5
#define el 14
#define er 17
#define buzzer 4
#define indicator 2
#define FRAME_COUNT sizeof(frames) / sizeof(frames[0])
int frame = 0;
const int button[6] = { lb, rb, l1, r1, el, er };
const int joystick_pin[4] = { lx, ly, rx, ry };
int joystick[4], joy_max[4], joy_min[4], joy_mid[4];
int button_val[8];
int temp[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
long Lposition, Rposition, lastPosL, lastPosR;
bool ble_connection = 0;


void setup() {
  Serial.begin(115200);
  display.begin(0x02, 0x3C);
  display.setTextColor(1);
  display.setTextSize(2);
  EEPROM.begin(512);
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  esp_bt_controller_init(&bt_cfg);
  esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
  esp_bredr_tx_power_set(ESP_PWR_LVL_P4, ESP_PWR_LVL_P7);  // Set max power

  for (byte i = 0; i < 4; i++) {
    joy_mid[i] = EEPROM.read(i) * 16;
    joy_min[i] = EEPROM.read(i + 2) * 16;
    joy_max[i] = EEPROM.read(i + 4) * 16;
  }
  for (byte i = 0; i < 6; i++) pinMode(button[i], INPUT_PULLUP);
  pinMode(indicator, OUTPUT);
  Lencoder.attachHalfQuad(26, 27);
  Rencoder.attachHalfQuad(15, 16);
  for (int i = 0; i < 5; i++) playNote(startupMelody[i], 100);
}

void loop() {
  home_screen();
  if (push(r1)) {
    for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
    byte r = menu();
    if (r) {
      for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
      if (r == 1) connection_panel();
      if (r == 2) ble_joystick();
      if (r == 3) {
        display.clearDisplay();
        text("CALIBRATE", 11, 24);
        display.display();
        cal();
        display.clearDisplay();
        display.setTextSize(1);
        for (byte i = 0; i < 4; i++)
          text(String(joy_min[i]) + "    " + String(joy_mid[i]) + "    " + String(joy_max[i]), 11, i * 12 + 10);
        display.display();
        while (!push(r1))
          ;
        display.setTextSize(2);
      }
      if (r == 4) pot_display();
      if (r == 5) button_display();
      if (r == 6) console_display();
      if (r == 7) snake_game();
      if (r == 8) DXBall();
      if (r == 9) space_game();
      if (r == 10) moto_racing();
    }
    display.setTextSize(2);
    for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
  }
}

void playNote(int frequency, int duration) {
  tone(buzzer, frequency, duration);
}
