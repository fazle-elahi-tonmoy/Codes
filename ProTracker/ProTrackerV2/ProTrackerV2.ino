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


// পিন ডেফাইন
#define TFT_CS 5   // ডিসপ্লে CS পিন
#define TFT_DC 3   // ডিসপ্লে DC পিন
#define TFT_RST 8  // ডিসপ্লে RST পিন
#define SD_CS 21   // SD কার্ড CS পিন
#define OK_PIN 14
#define Back_PIN 25
#define Maintanance_PIN 26
#define Help_PIN 27
#define POW_PIN 33
#define WiFi_PIN 32
#define buzzer 15


// ডিসপ্লে অবজেক্ট তৈরি
TFT_eSPI tft = TFT_eSPI();

bool power_state = 0;

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
  starting_sequence();
  tft.fillScreen(TFT_WHITE);
  disp_wifi();

  WiFi.mode(WIFI_STA);
  wm.autoConnect("WiFi Setup");
  welcome_screen();

  // sendHttpRequest();
}

void loop() {
  if (!digitalRead(OK_PIN)) {
    hourlyAchievement++;
    String value;
    if (hourlyAchievement < 10) value = " " + String(hourlyAchievement) + "  ";
    else if (hourlyAchievement < 100) value = String(hourlyAchievement) + "  ";
    else value = String(hourlyAchievement) + " ";
    tft.drawString(value, 345, 190);
    delay(1000);
  }
  starting_sequence();
  if (!digitalRead(WiFi_PIN)) {
    delay(20);
    uint16_t t = 0;
    while (!digitalRead(WiFi_PIN)) {
      delay(20);
      t++;
      if (t > 250) {
        wm.ResetSettings();
        wm.autoConnect("WiFi Setup");
        ESP.restart();
      }
    }
  }
}
