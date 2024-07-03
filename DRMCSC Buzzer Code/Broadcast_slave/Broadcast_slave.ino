#include <esp_now.h>
#include <WiFi.h>

#define sw 15
#define green 4
#define red 2

int send = 7; //this is the serial number of the buzzer

bool state = 1, message = 0;  // Flag to send data only once
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
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
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
  if (!digitalRead(sw) && state) {
    Serial.println("Button Pressed!");
    result = esp_now_send(broadcastAddress, (uint8_t*)&send, sizeof(send));
    Serial.println(result == ESP_OK ? "Sent with success" : "Sending Failed");
    state = 0;
    timer = millis();
  }
  if (message) {
    message = 0;
    int x = incomingReadings.but_status;
    Serial.println(x);
    if (x == send * 10) {
      digitalWrite(green, 1);
      digitalWrite(red, 0);
    } else if (x == 0) {
      digitalWrite(green, 0);
      digitalWrite(red, 1);
    }
  }
  if (millis() - timer > 1000) state = 1;
}
