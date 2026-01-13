#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ================= CONFIG ================= */
int relay[2] = { 27, 26 };  // relay[0]=27, relay[1]=26

#define PRESSURE1_PIN 33
#define PRESSURE2_PIN 35
#define MQ2_PIN 32
#define OFFSET 340

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

uint8_t broadcastAddress[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/* ================= STATE ================= */
String myMAC;
int setP = 50;
int currentCylinder = 1;
unsigned long lastHubPacket = 0;

int dispP1 = 0, dispP2 = 0, dispMQ2 = 0;

/* ================= RELAY (UNCHANGED) ================= */
void relay_state(bool a) {
  (a) ? digitalWrite(relay[0], 1) : digitalWrite(relay[1], 0);
  delay(1000);
  (a) ? digitalWrite(relay[1], 1) : digitalWrite(relay[0], 0);
  delay(5000);
}

/* ================= ESP-NOW CALLBACKS ================= */
void onDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  // optional debug
}

void onDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  String msg;
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];
  Serial.println(msg);

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, msg)) return;

  const char* rxMac = doc["mac"];
  if (!rxMac) return;
  if (strcmp(rxMac, myMAC.c_str()) != 0) return;

  lastHubPacket = millis();

  const char* cv = doc["change_value"];
  if (cv && strcmp(cv, "y") == 0) {
    setP = doc["setP"] | setP;
  }

  const char* chv = doc["change_valve"];
  if (chv && strcmp(chv, "y") == 0) {
    relay_state(currentCylinder == 1);
    currentCylinder = (currentCylinder == 1) ? 2 : 1;
  }

  int p1 = map(analogRead(PRESSURE1_PIN) - 360, 0, 4095, 0, 10000);
  int p2 = map(analogRead(PRESSURE2_PIN) - 380, 0, 4095, 0, 10000);
  int mq2 = analogRead(MQ2_PIN);
  p1 = constrain(p1, 0, 10000);
  p2 = constrain(p2, 0, 10000);

  bool lowTrig = (currentCylinder == 1) ? (p1 < setP) : (p2 < setP);

  dispP1 = p1;
  dispP2 = p2;
  dispMQ2 = mq2;

  StaticJsonDocument<256> out;
  out["pressure1"] = p1;
  out["pressure2"] = p2;
  out["mq2"] = mq2;
  out["low_pressure_triggered"] = lowTrig ? "y" : "n";
  out["current_cylinder"] = currentCylinder;

  char buf[256];
  size_t n = serializeJson(out, buf);
  esp_now_send(broadcastAddress, (uint8_t*)buf, n);
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

/* ================= OLED ================= */
void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Gas Controller");

  display.setCursor(0, 14);
  display.printf("C1: %d\n", dispP1);

  display.setCursor(0, 24);
  display.printf("C2: %d\n", dispP2);

  display.setCursor(0, 34);
  display.printf("MQ2: %d\n", dispMQ2);

  display.setCursor(0, 46);
  if (lastHubPacket == 0)
    display.print("Last: never");
  else
    display.printf("Last: %lus", (millis() - lastHubPacket) / 1000);

  display.display();
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);

  pinMode(relay[0], OUTPUT);
  pinMode(relay[1], OUTPUT);

  WiFi.mode(WIFI_STA);
  myMAC = WiFi.macAddress();
  Serial.println(myMAC);
  setupEspNow();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  analogSetAttenuation(ADC_11db);
}

/* ================= LOOP ================= */
void loop() {
  static unsigned long t = 0;
  if (millis() - t > 1000) {
    t = millis();
    updateOLED();
  }

  // Serial.printf("%d    %d\n", analogRead(33), analogRead(35));
  delay(10);
}
