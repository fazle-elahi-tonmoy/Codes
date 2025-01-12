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
HTTPClient http;

int hourlyTarget, hourlyAchievement, dailyTarget, dailyAchievement, defectQuantity;
float cycleTime;
String machineMac, user, machineNo, buyer, style, workingHour, npt, process, npt_start_time, npt_status;
String main_url = "http://163.47.84.201:9090/garments-pro/protracker/sewing-droplets/iot/";


#define SD_CS 21  // SD কার্ড CS পিন
#define OK_PIN 14
#define Back_PIN 27
#define Maintanance_PIN 26
#define Help_PIN 25
#define POW_PIN 33
#define WiFi_PIN 32
#define buzzer 13
#define active_LED 16
#define API_OK_LED 17
#define API_FAIL_LED 22
#define NPT_LED 19

#define press_time 3


// ডিসপ্লে অবজেক্ট তৈরি
TFT_eSPI tft = TFT_eSPI();

uint32_t press_timer, npt_timer;
bool npt_mode = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(active_LED, OUTPUT);
  pinMode(API_FAIL_LED, OUTPUT);
  pinMode(API_OK_LED, OUTPUT);
  pinMode(NPT_LED, OUTPUT);
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
  sendSummeryRequest();
  main_screen_update(1);
}

void loop() {
  if (!npt_mode) {

    if (!digitalRead(OK_PIN) && millis() - press_timer > press_time * 1000) {
      press_timer = millis();
      sendOKrequest();
    }

    if (!digitalRead(Back_PIN)) {
      digitalWrite(active_LED, 1);
      main_screen_update(1);
      delay(1000);
    }

    if (!digitalRead(Help_PIN)) {
      bool check = sendData("/help");
      if (check) {
        digitalWrite(active_LED, 0);
        tft.fillScreen(TFT_WHITE);
        tft.setTextColor(TFT_BLACK);
        tft.setFreeFont(FSSB24);
        tft.setTextDatum(MC_DATUM);
        tft.drawString("Help Requested", 240, 160);
      }
      delay(1000);
    }

    if (!digitalRead(Maintanance_PIN)) {
      bool check = sendData("/maintenance");
      if (check) {
        digitalWrite(active_LED, 0);
        tft.fillScreen(TFT_WHITE);
        tft.setTextColor(TFT_BLACK);
        tft.setFreeFont(FSSB18);
        tft.setTextDatum(MC_DATUM);
        tft.drawString("Maintanance Requested", 240, 160);
      }
      delay(1000);
    }

    if (long_press(WiFi_PIN, 250)) {
      wm.resetSettings();
      ESP.restart();
    }
  }

  if (millis() - npt_timer > 3000) {
    npt_timer = millis();
    checkNPT();
  }


  if (long_press(POW_PIN, 150)) {
    digitalWrite(active_LED, 0);
    digitalWrite(NPT_LED, 0);

    ESP.restart();
  }
}
