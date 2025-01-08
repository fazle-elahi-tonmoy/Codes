#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use hardware serial port 1 for DFPlayer Mini
#define RX_PIN 22  // ESP32 RX1
#define TX_PIN 23  // ESP32 TX1

HardwareSerial mySerial(1);  // Use Serial1
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);                              // Debugging serial monitor
  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // Initialize Serial1 for DFPlayer

  Serial.println("Initializing DFPlayer Mini...");
  if (!myDFPlayer.begin(mySerial)) {  // Use hardware serial to communicate with DFPlayer Mini
    Serial.println("DFPlayer Mini initialization failed!");
    Serial.println("1. Check connections.");
    Serial.println("2. Insert an SD card with audio files.");
    while (true)
      ;
  }

  Serial.println("DFPlayer Mini initialized successfully!");
  myDFPlayer.volume(30);  // Set volume (0 to 30)
  Serial.println("Playing track 1...");
  myDFPlayer.play(1);
}

void loop() {
}
