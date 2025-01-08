#include <TFT_eSPI.h>  // ILI9488 ডিসপ্লে লাইব্রেরি
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "fonts.h"
#include "bitmap.h"

const char *ssid = "CIFT";
const char *password = "cift@1971";
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


// ডিসপ্লে অবজেক্ট তৈরি
TFT_eSPI tft = TFT_eSPI();

int toggleState = 0;  // ইমেজ টগল স্টেট

void setup() {
  // সিরিয়াল মনিটর চালু
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);         // ডিসপ্লে রোটেশন সেট (1 মানে ল্যান্ডস্কেপ মোড)
  tft.fillScreen(TFT_BLACK);  // ডিসপ্লে কালো করে সেট করুন
  welcome_screen();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println("ESP32 MAC Address: " + WiFi.macAddress());

  // SD কার্ড ইনিশিয়ালাইজ
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    // tft.setTextColor(TFT_RED, TFT_BLACK);
    // tft.setTextDatum(MC_DATUM);
    // tft.drawString("SD Card Failed!", tft.width() / 2, tft.height() / 2);
    while (true)
      ;  // যদি SD কার্ড কাজ না করে, সিস্টেম বন্ধ
  }
  Serial.println("SD Card initialized.");

  // বাটন পিন ইনপুট মোডে সেট করা
  pinMode(OK_PIN, INPUT_PULLUP);
  pinMode(Back_PIN, INPUT_PULLUP);
  pinMode(Maintanance_PIN, INPUT_PULLUP);
  pinMode(Help_PIN, INPUT_PULLUP);
  pinMode(POW_PIN, INPUT_PULLUP);
  pinMode(WiFi_PIN, INPUT_PULLUP);

  // প্রথম ইমেজ দেখাও
  showBMP("/Main.bmp", 0, 0);
  sendHttpRequest();
}

void loop() {
  if (!digitalRead(OK_PIN)) {
    hourlyAchievement++;
    String value;
    if (hourlyAchievement < 10) value = " " + String(hourlyAchievement) + "  ";
    else if (hourlyAchievement < 100) value = String(hourlyAchievement) + "  ";
    else value = String(hourlyAchievement)+" ";
    tft.drawString(value, 345, 190);
    delay(1000);
  }
}


