#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoJson.h>
#define buzzer 3

RF24 radio(9, 10);  // CE, CSN
const byte addresses[6] = "radio1";
int value = 1111;

uint32_t timer;


void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Radio Failed!");
  }
  radio.openReadingPipe(0, addresses);
  radio.setPALevel(RF24_PA_MIN);
  radio.setPayloadSize(sizeof(value));
  radio.startListening();
  pinMode(buzzer, OUTPUT);
}

void loop() {
  if (radio.available()) {
    radio.read(&value, sizeof(value));
    int x = ((value / 100) - 12);
    int y = ((value % 100) - 12);
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["x_coordinate"] = x * 20;
    jsonDoc["y_coordinate"] = y * 20;
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    Serial.println(jsonString);
    delay(200);
    if (value == 6666) {
      digitalWrite(buzzer, 1);
      delay(200);
      digitalWrite(buzzer, 0);
      delay(100);
      digitalWrite(buzzer, 1);
      delay(100);
      digitalWrite(buzzer, 0);
    } else {
      digitalWrite(buzzer, 1);
      delay(100);
      digitalWrite(buzzer, 0);
    }
  }
}