#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

#include "icons_rgb565.h"
#include "Free_Fonts.h"

TFT_eSPI tft = TFT_eSPI();


// ---------------- CONFIG ----------------
const char *WIFI_SSID = "ROBOTICS";
const char *WIFI_PASS = "robotics";
const char *WEBAPP_URL = "https://script.google.com/macros/s/AKfycbxYwtxuNiu-1r7ottmfWWjPA2PMoz3XyWqkyGI8uVfKx4hpqqBqVjN4ZKB97rAyo9QJ/exec";  // replace if needed

// RFID pins
#define RFID_SS_PIN 5
#define RFID_RST_PIN 0

// Relays (Active HIGH) - product index order: Stapler, Pin, Red Pen, Black Pen
const int RELAY_PINS[4] = { 26, 27, 14, 12 };

// Calibration button
#define BTN_CAL_PIN 22

// Product names (must match spreadsheet product names)
const char *PRODUCT_NAMES[4] = { "Stapler", "Pin", "Red Pen", "Black Pen" };

// RFID
MFRC522 mfrc(RFID_SS_PIN, RFID_RST_PIN);

// Product info structure & array
struct ProdInfo {
  String name;
  int stock;
  float price;
  unsigned long timeMs;  // per-unit dispense time from spreadsheet
};
ProdInfo products[4];

// User & selection
String userUID = "";
String userName = "";
float userBalance = 0.0;
int selectedQty[4] = { 0, 0, 0, 0 };

// Screen sizes
const int SCREEN_W = 480;
const int SCREEN_H = 320;

// UI layout constants (keep consistent with draw function)
const int ICON_SIZE = 48;

// Dispense queue structure (internal)
struct DispItem {
  int index;
  int units;
  unsigned long unitTime;
};
DispItem dispQueue[16];  // small queue, up to 16 entries (we only need up to 4)
int dispQueueLen = 0;
int dispQueuePos = 0;

// Dispense state
bool dispensing = false;
bool dispRelayOn = false;
unsigned long dispUnitStartMs = 0;

// ---------- DEBUG ----------
void dbg(const String &s) {
  Serial.println(s);
}

// ---------------- Setup & main loop ----------------
void setup() {
  Serial.begin(115200);
  dbg("[BOOT] Vending machine starting");

  // pins
  for (int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], LOW);
  }
  pinMode(BTN_CAL_PIN, INPUT_PULLUP);

  // display
  tft.init();
  tft.setRotation(1);
  // If your TFT_eSPI needs a swap, you would set it elsewhere. Keep as-is.

  // touch calibration on startup if button pressed
  if (digitalRead(BTN_CAL_PIN) == HIGH) {
    dbg("[BOOT] Calibration button pressed; running calibration");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Touch Calibration", SCREEN_W / 2, SCREEN_H / 2, 4);
    tft.calibrateTouch(nullptr, TFT_MAGENTA, TFT_BLACK, 15);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Calibration Finished!", SCREEN_W / 2, SCREEN_H / 2, 4);
    delay(1000);
    dbg("[BOOT] Calibration finished");
  }

  // SPI & RFID
  SPI.begin();
  mfrc.PCD_Init();
  dbg("[RFID] Initialized");

  // WiFi & get initial prices
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Connecting WiFi", SCREEN_W / 2, SCREEN_H / 2, 4);
  dbg("[WIFI] connecting...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(200);
  dbg("[WIFI] connected: " + WiFi.localIP().toString());

  if (!getPricesFromServer()) {
    dbg("[DATA] Failed to fetch initial product data");
  }

  drawDefaultScreen();
}

void loop() {
  // RFID detection: if card present - verify and go to product selection
  if (mfrc.PICC_IsNewCardPresent() && mfrc.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < mfrc.uid.size; i++) {
      if (mfrc.uid.uidByte[i] < 0x10) uid += "0";
      uid += String(mfrc.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    dbg("[RFID] Card detected: " + uid);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Verifying...", SCREEN_W / 2, SCREEN_H / 2, 4);

    if (verifyUID(uid)) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.setTextDatum(MC_DATUM);
      tft.drawString("Verified!", SCREEN_W / 2, SCREEN_H / 2, 4);
      delay(500);
      // refresh server data
      getPricesFromServer();
      // reset selectedQty
      for (int i = 0; i < 4; i++) selectedQty[i] = 0;
      // show product UI
      drawProductSelectionScreen();

      // product selection loop (runs until user cancels or completes a purchase)
      bool inSelection = true;
      while (inSelection) {
        // check touch
        uint16_t sx, sy;
        if (tft.getTouch(&sx, &sy)) {
          dbg("[TOUCH] " + String(sx) + "," + String(sy));
          int touched = getTouchedElement(sx, sy);
          dbg("[TOUCH] code " + String(touched));
          if (touched >= 0 && touched <= 3) {
            // minus
            int idx = touched;
            if (selectedQty[idx] > 0) {
              selectedQty[idx]--;
              dbg("[SELECT] Decreased " + products[idx].name + " -> " + String(selectedQty[idx]));
              drawProductSelectionScreen();
            } else {
              dbg("[SELECT] already zero for " + products[idx].name);
            }
            delay(180);  // crude debounce
          } else if (touched >= 20 && touched <= 23) {
            // plus
            int idx = touched - 20;
            if (selectedQty[idx] < products[idx].stock) {
              selectedQty[idx]++;
              dbg("[SELECT] Increased " + products[idx].name + " -> " + String(selectedQty[idx]));
              drawProductSelectionScreen();
            } else {
              dbg("[SELECT] cannot exceed stock for " + products[idx].name);
            }
            delay(180);
          } else if (touched == 100) {
            dbg("[UI] Cancel pressed");
            inSelection = false;
            drawDefaultScreen();
            break;
          } else if (touched == 101) {
            dbg("[UI] OK pressed - checking balance");
            // compute total
            float total = 0;
            for (int i = 0; i < 4; i++) total += selectedQty[i] * products[i].price;
            dbg("[UI] Total = " + String(total, 2) + " balance = " + String(userBalance, 2));
            if (total > userBalance) {
              dbg("[UI] LOW Balance");
              tft.fillScreen(TFT_BLACK);
              tft.setTextColor(TFT_RED);
              tft.setTextDatum(MC_DATUM);
              tft.drawString("LOW Balance", SCREEN_W / 2, SCREEN_H / 2, 4);
              delay(2000);
              // redraw selection
              drawProductSelectionScreen();
              continue;
            }
            // prepare items json
            DynamicJsonDocument jdoc(1024);
            JsonObject items = jdoc.createNestedObject("items");
            for (int i = 0; i < 4; i++)
              if (selectedQty[i] > 0) items[products[i].name] = selectedQty[i];

            if (items.isNull() || items.size() == 0) {
              dbg("[UI] No items selected");
              // do nothing
              continue;
            }
            tft.fillScreen(TFT_BLACK);
            tft.setTextColor(TFT_WHITE);
            tft.setTextDatum(MC_DATUM);
            tft.drawString("Purchasing Product", SCREEN_W / 2, SCREEN_H / 2, 4);

            DynamicJsonDocument respDoc(2048);
            if (!postPurchaseAndUpdate(userUID, total, items, respDoc)) {
              dbg("[SERVER] Purchase failed");
              tft.fillScreen(TFT_BLACK);
              tft.setTextColor(TFT_RED);
              tft.setTextDatum(MC_DATUM);
              tft.drawString("Purchase Failed", SCREEN_W / 2, SCREEN_H / 2, 4);
              delay(2000);
              drawProductSelectionScreen();
              continue;
            }

            // successful purchase: start dispensing
            tft.fillScreen(TFT_BLACK);
            tft.setTextColor(TFT_WHITE);
            tft.setTextDatum(MC_DATUM);
            tft.drawString("Dispensing, Please collect", SCREEN_W / 2, SCREEN_H / 2, 4);
            dbg("[PURCHASE] Server accepted purchase - starting dispense");
            startDispenseQueue();  // build queue & set dispensing flag

            // while dispensing, process in loop
            while (dispensing) {
              processDispense();
              delay(10);
            }

            // After dispensing finished, show thanks and return to default
            tft.fillScreen(TFT_BLACK);
            tft.setTextColor(TFT_GREEN);
            tft.setTextDatum(MC_DATUM);
            tft.drawString("Done. Thank you!", SCREEN_W / 2, SCREEN_H / 2, 4);
            dbg("[DISPENSE] Completed");
            delay(1500);
            drawDefaultScreen();
            inSelection = false;
            break;
          }
        }  // touch check

        // also process dispense background (if somehow started elsewhere)
        processDispense();
        delay(20);
      }
    }

    else {
      dbg("[RFID] Verify failed");
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_RED);
      tft.setTextDatum(MC_DATUM);
      tft.drawString("Wrong ID Card, Please Try again!", SCREEN_W / 2, SCREEN_H / 2, 4);
      delay(2000);
      drawDefaultScreen();
    }  // Properly end RFID session and reinitialize reader
    mfrc.PICC_HaltA();
    mfrc.PCD_StopCrypto1();
    delay(50);
    mfrc.PCD_Init();  // ✅ reinit the RFID reader so new cards are detected
  }  // end RFID present

  // main loop background tasks
  // processDispense();
  delay(10);
}
