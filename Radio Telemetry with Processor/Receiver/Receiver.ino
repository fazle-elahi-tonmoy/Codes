#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  if (!radio.begin()) {
    Serial.println("Failed!");
    while (1)
      ;
  }
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, address);
  radio.startListening();
  digitalWrite(14, 1);
}

void loop() {
  if (radio.available()) {
    char text[50] = { 0 };
    radio.read(&text, sizeof(text));
    Serial.print(text);
    digitalWrite(14, LOW);
    delay(100);
    digitalWrite(14, HIGH);
  }
}