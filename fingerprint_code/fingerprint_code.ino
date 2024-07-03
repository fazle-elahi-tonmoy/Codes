#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(2, 3);
#define yellow A2
#define blue A3
#define red A4
#define relay 6
#define buzzer A0
#define BUTTON_PIN 4

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, 1);
  finger.begin(57600);
}

void loop() {
  byte r = push(BUTTON_PIN);
  if (r == 1) {
    digitalWrite(relay, 0);
    digitalWrite(blue, 1);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(relay, 1);
    digitalWrite(blue, 0);
  } else if (r == 2) enrollFingerprint();
  getFingerprintID();
}