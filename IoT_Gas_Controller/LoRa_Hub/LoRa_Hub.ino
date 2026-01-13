#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>

uint8_t broadcastAddress[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

const char TARGET_MAC[] = "EC:E3:34:19:9C:28";  // controller MAC

int setP = 50;
char change_value = 'n';
char change_valve = 'n';

/* ================= ESP-NOW CALLBACKS ================= */
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  String msg;
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];
  Serial.println(msg);

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, msg)) return;

  int p1 = doc["pressure1"] | 0;
  int p2 = doc["pressure2"] | 0;
  int cyl = doc["current_cylinder"] | 0;
  const char* low = doc["low_pressure_triggered"];

  if (low && strcmp(low, "y") == 0) {
    bool ok = (cyl == 1 && p2 > 300) || (cyl == 2 && p1 > 300);
    if (ok) {
      change_valve = 'y';
      Serial.println("Valve switch approved");
    } else {
      Serial.println("SYSTEM ERROR");
    }
  }
}

/* ================= ESP-NOW SETUP ================= */
void setupEspNow() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(onDataSent);
  esp_now_register_recv_cb(onDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_err_t res = esp_now_add_peer(&peerInfo);
  if (res == ESP_OK) Serial.println("Broadcast peer added");
  else if (res == ESP_ERR_ESPNOW_EXIST) Serial.println("Broadcast peer exists");
  else Serial.printf("Peer add failed: %d\n", res);
}

/* ================= SEND ================= */
void sendCommand() {
  StaticJsonDocument<128> doc;
  doc["mac"] = TARGET_MAC;
  doc["change_value"] = String(change_value);
  doc["setP"] = setP;
  doc["change_valve"] = String(change_valve);

  char buf[128];
  size_t n = serializeJson(doc, buf);

  esp_now_send(broadcastAddress, (uint8_t*)buf, n);

  change_valve = 'n';   // AUTO RESET SAFETY
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  setupEspNow();
  Serial.println("Hub ready");
}

/* ================= LOOP ================= */
void loop() {
  static unsigned long t = 0;
  if (millis() - t > 5000) {
    t = millis();
    sendCommand();
  }
}
