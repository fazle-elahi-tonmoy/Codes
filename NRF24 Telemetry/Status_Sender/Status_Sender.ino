#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
DHT dht(25, DHT11);
RF24 radio(15, 5);  // CE, CSN
const byte addresses[6] = "00001";

const int MQ2 = 32, MQ135 = 33, MQ7 = 34;
int value[3];
String message = "";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  if (!radio.begin()) {
    Serial.println("Radio Failed!");
    while (1) {
      digitalWrite(2, 1);
      delay(100);
      digitalWrite(2, 0);
      delay(100);
    }
  }
  radio.openWritingPipe(addresses);
  radio.setPALevel(RF24_PA_MIN);
  dht.begin();
  delay(2000);
}

void loop() {
  value[0] = analogRead(MQ2);
  value[1] = analogRead(MQ7);
  value[2] = analogRead(MQ135);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  message = "1)" + String(value[0]);
  Serial.print(message + " ");
  radio.write(&message, sizeof(message));
  message = "2)" + String(value[1]);
  Serial.print(message + " ");
  radio.write(&message, sizeof(message));
  message = "3)" + String(value[2]);
  Serial.print(message + " ");
  radio.write(&message, sizeof(message));;
  message = "4)" + String(t, 1);
  Serial.print(message + " ");
  radio.write(&message, sizeof(message));
  message = "5)" + String(h, 1);
  Serial.println(message + " ");
  radio.write(&message, sizeof(message));
  
  delay(2000);
}