#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>

/* ================= CONFIG ================= */
int relay[2] = { 27, 26 };

#define PRESSURE1_PIN 33
#define PRESSURE2_PIN 35
#define MQ2_PIN 32
#define CALIB_BTN 0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Preferences prefs;

uint8_t broadcastAddress[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/* ================= STATE ================= */
String myMAC;
int setP = 50;
int currentCylinder = 1;
unsigned long lastHubPacket = 0;

int dispP1 = 0, dispP2 = 0, dispMQ2 = 0;

/* ================= CALIBRATION ================= */
enum CalState {
  CAL_IDLE,
  CAL_EMPTY,
  CAL_S1_MAX,
  CAL_S2_MAX,
  CAL_DONE
};

CalState calState = CAL_IDLE;
bool calibrationMode = false;

unsigned long btnPressTime = 0;
bool btnLast = HIGH;

/* calibration values */
int empty1 = 360, empty2 = 380;
int max1 = 4095, max2 = 4095;

/* ================= RELAY ================= */
void relay_state(bool a) {
  (a) ? digitalWrite(relay[0], 1) : digitalWrite(relay[1], 0);
  delay(1000);
  (a) ? digitalWrite(relay[1], 1) : digitalWrite(relay[0], 0);
  delay(5000);
}

/* ================= BUTTON ================= */
bool shortPress = false;
bool longPress = false;

void handleButton() {
  bool btn = digitalRead(CALIB_BTN);

  if (btn == LOW && btnLast == HIGH) {
    btnPressTime = millis();
  }

  if (btn == HIGH && btnLast == LOW) {
    unsigned long dur = millis() - btnPressTime;
    if (dur >= 500) longPress = true;
    else shortPress = true;
  }

  btnLast = btn;
}

/* ================= OLED ================= */
void showCalScreen(const char* l1, const char* l2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println(l1);
  display.setCursor(0, 30);
  display.println(l2);
  display.display();
}

void updateOLED() {
  if (calibrationMode) return;

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

/* ================= CALIBRATION FSM ================= */
void calibrationFSM() {
  if (!calibrationMode) {
    if (longPress && btnPressTime > 1000) {
      calibrationMode = true;
      calState = CAL_EMPTY;
      showCalScreen("Calibration Mode", "Press to Continue");
    }
    return;
  }

  if (longPress) {
    calibrationMode = false;
    calState = CAL_IDLE;
    showCalScreen("Calibration", "Cancelled");
    delay(1500);
    return;
  }

  if (!shortPress) return;

  shortPress = false;

  switch (calState) {
    case CAL_EMPTY:
      showCalScreen("Empty value", "Press to Confirm");
      empty1 = analogRead(PRESSURE1_PIN);
      empty2 = analogRead(PRESSURE2_PIN);
      calState = CAL_S1_MAX;
      break;

    case CAL_S1_MAX:
      showCalScreen("Sensor 1 Max", "Press to Confirm");
      max1 = analogRead(PRESSURE1_PIN);
      calState = CAL_S2_MAX;
      break;

    case CAL_S2_MAX:
      showCalScreen("Sensor 2 Max", "Press to Confirm");
      max2 = analogRead(PRESSURE2_PIN);
      calState = CAL_DONE;
      break;

    case CAL_DONE:
      prefs.begin("cal", false);
      prefs.putInt("e1", empty1);
      prefs.putInt("e2", empty2);
      prefs.putInt("m1", max1);
      prefs.putInt("m2", max2);
      prefs.end();

      showCalScreen("Calibration", "Complete");
      delay(2000);

      calibrationMode = false;
      calState = CAL_IDLE;
      break;

    default: break;
  }
}

/* ================= ESP-NOW CALLBACKS ================= */
void onDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  // Serial.printf("Send status: %s\n", status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "FAIL");
}

/* ================= ESP-NOW ================= */
void onDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  if (calibrationMode) return;

  String msg;
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];
  // Serial.print("Received: ");
  // Serial.println(msg);
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, msg)) return;

  if (strcmp(doc["mac"], myMAC.c_str()) != 0) {
    Serial.println("NO MATCH");
    return;
  }
  // Serial.println("PINGED!");
  lastHubPacket = millis();

  if (strcmp(doc["change_valve"] | "n", "y") == 0) {
    relay_state(currentCylinder == 1);
    currentCylinder = (currentCylinder == 1) ? 2 : 1;
  }

  int raw1 = analogRead(PRESSURE1_PIN);
  int raw2 = analogRead(PRESSURE2_PIN);

  int p1 = map(raw1 - empty1, 0, max1 - empty1, 0, 2000);
  int p2 = map(raw2 - empty2, 0, max2 - empty2, 0, 2000);

  p1 = constrain(p1, 0, 10000);
  p2 = constrain(p2, 0, 10000);

  dispP1 = p1;
  dispP2 = p2;
  dispMQ2 = analogRead(MQ2_PIN);

  bool low = (currentCylinder == 1) ? (p1 < setP) : (p2 < setP);

  StaticJsonDocument<256> out;
  out["pressure1"] = p1;
  out["pressure2"] = p2;
  out["mq2"] = dispMQ2;
  out["low_pressure_triggered"] = low ? "y" : "n";
  out["current_cylinder"] = currentCylinder;

  char buf[256];
  size_t n = serializeJson(out, buf);
  esp_now_send(broadcastAddress, (uint8_t*)buf, n);
}

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

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  pinMode(relay[0], OUTPUT);
  pinMode(relay[1], OUTPUT);
  pinMode(CALIB_BTN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  myMAC = WiFi.macAddress();
  Serial.println(myMAC);
  setupEspNow();

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  analogSetAttenuation(ADC_11db);

  prefs.begin("cal", true);
  empty1 = prefs.getInt("e1", empty1);
  empty2 = prefs.getInt("e2", empty2);
  max1 = prefs.getInt("m1", max1);
  max2 = prefs.getInt("m2", max2);
  prefs.end();
}

/* ================= LOOP ================= */
void loop() {
  handleButton();
  calibrationFSM();

  static unsigned long t = 0;
  if (millis() - t > 1000) {
    t = millis();
    updateOLED();
  }

  longPress = shortPress = false;
  delay(10);
}
