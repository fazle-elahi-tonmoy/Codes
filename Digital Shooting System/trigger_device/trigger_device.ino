#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10);  // CE, CSN
const byte addresses[7] = "trigger";
#define button 4
#define buzzer 3
#define laser 8
int value = 1111;

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Radio Failed!");
  }
  radio.openWritingPipe(addresses);
  radio.setPALevel(RF24_PA_MIN);
  radio.setPayloadSize(sizeof(value));
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(laser, OUTPUT);
}

void loop() {
  if (!digitalRead(button)) {
    digitalWrite(laser, 1);
    delay(400);
    bool report = radio.write(&value, sizeof(value));
    (report) ? Serial.println("Message Sent: " + String(value)) : Serial.println("Sending Failed!");
    if (report) digitalWrite(buzzer, 1);
    delay(100);
    digitalWrite(buzzer, 0);
  }

  else {
    digitalWrite(laser, 0);
  }
}
