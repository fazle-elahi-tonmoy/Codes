#include <TFT_eSPI.h>  // ILI9488 ডিসপ্লে লাইব্রেরি
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "fonts.h"
#include "bitmap.h"
WiFiManager wm;

int hourlyTarget, hourlyAchievement, dailyTarget, dailyAchievement, defectQuantity;
float cycleTime;
String machineMac, user, machineNo, buyer, style, workingHour, npt, process;


#define SD_CS 21  // SD কার্ড CS পিন
#define OK_PIN 14
#define Back_PIN 27
#define Maintanance_PIN 26
#define Help_PIN 25
#define POW_PIN 33
#define WiFi_PIN 32
#define buzzer 15

#define press_time 5


// ডিসপ্লে অবজেক্ট তৈরি
TFT_eSPI tft = TFT_eSPI();

uint32_t press_timer;
bool npt_mode = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);
  pinMode(OK_PIN, INPUT_PULLUP);
  pinMode(Back_PIN, INPUT_PULLUP);
  pinMode(Maintanance_PIN, INPUT_PULLUP);
  pinMode(Help_PIN, INPUT_PULLUP);
  pinMode(POW_PIN, INPUT_PULLUP);
  pinMode(WiFi_PIN, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  //waiting to press the power button for 2 sec
  while (1) {
    if (long_press(POW_PIN, 100)) {
      digitalWrite(buzzer, 1);
      delay(100);
      digitalWrite(buzzer, 0);
      delay(100);
      digitalWrite(buzzer, 1);
      delay(100);
      digitalWrite(buzzer, 0);
      break;
    }
  }
  disp_wifi();
  WiFi.mode(WIFI_STA);
  wm.autoConnect("WiFi Setup");
  welcome_screen();
  delay(2000);
  sendHttpRequest();
  main_screen_update(1);
}

void loop() {
  if (!digitalRead(OK_PIN) && millis() - press_timer > press_time * 1000) {
    press_timer = millis();
    sendHttpRequest();
    main_screen_update(0);
  }

  if (!digitalRead(Maintanance_PIN)) {
    npt_mode = 1;
    npt_screen();
    delay(1000);
  }

  if (!digitalRead(Back_PIN)) {
    npt_mode = 0;
    main_screen_update(1);
    delay(1000);
  }

  if (long_press(POW_PIN, 150)) ESP.restart();
  if (long_press(WiFi_PIN, 250)) {
    wm.resetSettings();
    ESP.restart();
  }
}
