#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmap.h"
#include <LoRa.h>
#include <SPI.h>
#include <EEPROM.h>
#include "WiFi.h"
#include <WiFiManager.h>
#include <HTTPClient.h>
#define ss 5
#define rst 15
#define dio0 2
#define sw1 17
#define sw2 26
#define FRAME_COUNT sizeof(frames) / sizeof(frames[0])
int frame = 0;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
WiFiManager wm;

uint32_t refresh_timer;
int charge_time = 0;

// Google script Web_App_URL.
String Web_App_URL = "https://script.google.com/macros/s/AKfycbxuZBoEiejiOv-f4wR4yYROW4VvoYCSfc1lcPwL1t5OfiSszYDbl5Li3O8vZLAz5ip_/exec";
String str_modes = "atc";
String LoRaData, RFID, HubID;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(10);
  charge_time = EEPROM.read(0);
  display.begin(0x02, 0x3C);
  display.setTextColor(1);
  display.setTextSize(2);
  display.clearDisplay();
  text("CONNECTING", 4, 12);
  text("   WiFi   ", 4, 40);
  display.display();
  WiFi.mode(WIFI_STA);
  wm.autoConnect("WiFi Setup");
  display.clearDisplay();
  text("   WiFi   ", 4, 12);
  text("CONNECTED!", 4, 40);
  display.display();
  delay(1000);
  LoRa.setPins(ss, rst, dio0);  //setup LoRa transceiver module
  while (!LoRa.begin(433E6))
    ;
  LoRa.setSyncWord(0xA5);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
}

void loop() {
  home_screen();
  int packetSize = LoRa.parsePacket();  // try to parse packet
  if (packetSize) {
    bool approval = 0;
    display.clearDisplay();
    text("   Card   ", 4, 12);
    text(" Checking ", 4, 40);
    display.display();
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData + " ");
    }
    Serial.print(LoRa.packetRssi());
    HubID = getValue(LoRaData, ':', 0);
    if (HubID == "LoRa") {
      display.clearDisplay();
      text("   HUB   ", 11, 12);
      text("Responding", 4, 40);
      display.display();
      delay(5000);
    } else {
      RFID = getValue(LoRaData, ':', 1);
      String result = http_Req("atc", RFID, HubID);
      Serial.println(result);
      if (result == "start" || result == "stop") {
        display.clearDisplay();
        text("   Card   ", 4, 12);
        text(" Verified ", 4, 40);
        display.display();
        approval = 1;
      }

      else if (result == "atcErr01") {
        display.clearDisplay();
        text(" New Card ", 4, 8);
        text(" Approve? ", 4, 32);
        display.setTextSize(1);
        text("No                Yes", 1, 56);
        display.display();
        display.setTextSize(2);
        uint32_t waiting = millis();
        while (millis() - waiting < 10000) {
          byte l = push(sw1);
          byte r = push(sw2);
          if (l) break;
          else if (r) {
            approval = 1;
            break;
          }
        }
        if (approval) http_Req("reg", RFID, HubID);
        else {
          LoRa.beginPacket();
          LoRa.print(HubID + ":" + "error");
          LoRa.endPacket();
        }
      }

      else {
        display.clearDisplay();
        text("Sys Error!", 4, 0);
        text("  Please  ", 4, 24);
        text("Try Again!", 4, 48);
        display.display();
        LoRa.beginPacket();
        LoRa.print(HubID + ":" + "error");
        LoRa.endPacket();
      }

      delay(1000);
      if (approval) {
        LoRa.beginPacket();
        LoRa.print(HubID + ":" + result);
        LoRa.endPacket();
      }
    }
  }

  byte r = push(sw1);
  if (r == 2) {
    display.clearDisplay();
    text("   WiFi   ", 4, 12);
    text("SETUP MODE", 4, 40);
    display.display();
    wm.resetSettings();
    wm.autoConnect("WiFi Setup");
  }
  r = push(sw2);
  if (r == 2) timer_set();
}