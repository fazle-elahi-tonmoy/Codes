#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>

uint8_t broadcastAddress[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
const char TARGET_MAC[] = "EC:E3:34:19:9C:28";

int setP = 50;
char change_value = 'n';
char change_valve = 'n';

/* ===== NEW STATE ===== */
bool pendingRecheck = false;
unsigned long lastSwitchTime = 0;
int prevCylinder = 0;

/* ================= DEBUG ================= */
#define DBG(tag, fmt, ...) \
  Serial.printf("[%lu][HUB][%s] " fmt "\n", millis(), tag, ##__VA_ARGS__)

/* ================= ESP-NOW CALLBACKS ================= */
void onDataSent(const uint8_t *, esp_now_send_status_t status) {
  // DBG("TX", "Send status: %s", status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "FAIL");
}

void onDataRecv(const uint8_t *, const uint8_t *incomingData, int len) {
  String msg;
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];

  // DBG("RX", "Raw: %s", msg.c_str());

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, msg)) return;

  int p1 = doc["pressure1"];
  int p2 = doc["pressure2"];
  int cyl = doc["current_cylinder"];
  const char *low = doc["low_pressure_triggered"];

  DBG("DATA", "p1=%d p2=%d cyl=%d low=%s", p1, p2, cyl, low);

  /* ---------- LOW PRESSURE DETECT ---------- */
  if (low && strcmp(low, "y") == 0 && !pendingRecheck) {
    bool ok = (cyl == 1 && p2 > 300) || (cyl == 2 && p1 > 300);

    if (ok) {
      change_valve = 'y';
      pendingRecheck = true;
      lastSwitchTime = millis();
      prevCylinder = cyl;

      DBG("ACTION", "Switch approved, will recheck in 60s");
    }

    else {
      DBG("FAULT", "Backup cylinder invalid");
    }
  }

  /* ---------- DELAYED RECHECK ---------- */
  if (pendingRecheck && millis() - lastSwitchTime >= 60000) {
    DBG("CHECK", "Re-evaluating previous cylinder");

    bool recovered =
      (prevCylinder == 1 && p1 > 300) || (prevCylinder == 2 && p2 > 300);

    if (recovered) {
      DBG("ACTION", "Previous cylinder recovered, reverting");
      change_valve = 'y';
    }

    else {
      DBG("INFO", "No recovery detected");
    }

    pendingRecheck = false;
  }
}

/* ================= SEND ================= */
void sendCommand() {
  StaticJsonDocument<128> doc;
  doc["mac"] = TARGET_MAC;
  doc["change_value"] = String(change_value);
  doc["setP"] = setP;
  doc["change_valve"] = String(change_valve);

  char buf[128];
  serializeJson(doc, buf);

  // DBG("TX", "Command: %s", buf);
  esp_now_send(broadcastAddress, (uint8_t *)buf, strlen(buf));

  change_valve = 'n';
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  DBG("BOOT", "MAC: %s", WiFi.macAddress().c_str());

  esp_now_init();
  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, broadcastAddress, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  DBG("READY", "Hub online");
}

/* ================= LOOP ================= */
void loop() {
  static unsigned long t = 0;
  if (millis() - t > 5000) {
    t = millis();
    sendCommand();
  }
}
