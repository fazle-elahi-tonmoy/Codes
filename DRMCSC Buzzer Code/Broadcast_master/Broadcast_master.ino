#include <esp_now.h>
#include <WiFi.h>

#define sw 17
#define led 2

int send;

bool  message = 0, first = 1;  // Flag to send data only once
uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
bool incomingLED_status;
uint32_t timer;

typedef struct struct_message {
  int but_status;
} struct_message;

struct_message incomingReadings;
esp_now_peer_info_t peerInfo;
esp_err_t result;

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(sw, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(26, OUTPUT);
  digitalWrite(26, 0);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  byte r = push(sw);
  if (r == 1) {
    digitalWrite(led, 1);
    send = 0;
    first = 1;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&send, sizeof(send));
    Serial.println(result == ESP_OK ? "Sent with success" : "Sending Failed");
    timer = millis();
  }

  else if (r == 2) {
    for (byte i = 1; i <= 8; i++) {
      send = i * 10;
      esp_now_send(broadcastAddress, (uint8_t*)&send, sizeof(send));
      delay(1000);
      send = 0;
      esp_now_send(broadcastAddress, (uint8_t*)&send, sizeof(send));
    }
  }
  if (message) {
    message = 0;
    int x = incomingReadings.but_status;
    Serial.println(x);
    if (first) {
      send = x * 10;
      first = 0;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&send, sizeof(send));
      Serial.println(result == ESP_OK ? "Sent with success" : "Sending Failed");
    }
  }
  if (millis() - timer > 500) digitalWrite(led, 0);
}
