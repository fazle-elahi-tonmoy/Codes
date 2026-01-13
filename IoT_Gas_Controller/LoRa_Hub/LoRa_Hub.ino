#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>

uint8_t broadcastAddress[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const char TARGET_MAC[] = "EC:E3:34:19:9C:28";

int setP = 50;
char change_value = 'n';
char change_valve = 'n';

/* ===== RECOVERY LOGIC STATE ===== */
bool pendingRecheck = false;
unsigned long lastSwitchTime = 0;
int prevCylinder = 0;

/* ===== LAST DATA CACHE ===== */
int lastP1 = 0;
int lastP2 = 0;
int lastCylinder = 0;
bool lastLow = false;
bool lastBothEmpty = false;

/* ================= ESP-NOW CALLBACKS ================= */
void onDataSent(const uint8_t *, esp_now_send_status_t) {}

void onDataRecv(const uint8_t *, const uint8_t *incomingData, int len) {
  String msg;
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, msg)) return;

  int p1 = doc["pressure1"] | 0;
  int p2 = doc["pressure2"] | 0;
  int cyl = doc["current_cylinder"] | 0;
  const char* low = doc["low_pressure_triggered"];

  bool lowTrig = (low && strcmp(low, "y") == 0);
  bool bothEmpty = (p1 < setP && p2 < setP);

  /* ---------- LOW PRESSURE SWITCH ---------- */
  if (lowTrig && !pendingRecheck) {
    bool ok = (cyl == 1 && p2 > 300) || (cyl == 2 && p1 > 300);
    if (ok) {
      change_valve = 'y';
      pendingRecheck = true;
      lastSwitchTime = millis();
      prevCylinder = cyl;
    }
  }

  /* ---------- 60s RECOVERY RECHECK ---------- */
  if (pendingRecheck && millis() - lastSwitchTime >= 60000) {
    bool recovered =
      (prevCylinder == 1 && p1 > 300) ||
      (prevCylinder == 2 && p2 > 300);

    if (recovered) {
      change_valve = 'y';
    }
    pendingRecheck = false;
  }

  /* ---------- CACHE DATA ---------- */
  lastP1 = p1;
  lastP2 = p2;
  lastCylinder = cyl;
  lastLow = lowTrig;
  lastBothEmpty = bothEmpty;

  /* ---------- SERIAL JSON OUTPUT ---------- */
  StaticJsonDocument<256> out;
  out["pressure1"] = lastP1;
  out["pressure2"] = lastP2;
  out["current_cylinder"] = lastCylinder;
  out["low_pressure"] = lastLow;
  out["both_empty"] = lastBothEmpty;

  serializeJson(out, Serial);
  Serial.println();
}

/* ================= SEND COMMAND ================= */
void sendCommand() {
  StaticJsonDocument<128> doc;
  doc["mac"] = TARGET_MAC;
  doc["change_value"] = String(change_value);
  doc["setP"] = setP;
  doc["change_valve"] = String(change_valve);

  char buf[128];
  size_t n = serializeJson(doc, buf);
  esp_now_send(broadcastAddress, (uint8_t*)buf, n);

  change_valve = 'n';
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, broadcastAddress, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);
}

/* ================= LOOP ================= */
void loop() {
  static unsigned long t = 0;
  if (millis() - t > 5000) {
    t = millis();
    sendCommand();
  }
}
