#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2, 3);
uint8_t records[7];  // save record
uint8_t buf[64];

byte mf = 5, mb = 6;
const int led = 13, sw = 12;



void setup() {
  myVR.begin(9600);
  Serial.begin(115200);

  // if (!digitalRead(sw))
  //
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(mf, OUTPUT);
  pinMode(mb, OUTPUT);
  if (!digitalRead(sw)) training();
  myVR.load((uint8_t)0);
  myVR.load((uint8_t)1);
  myVR.load((uint8_t)2);
}

void loop() {
  int ret;
  ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    digitalWrite(led, 1);
    delay(100);
    digitalWrite(led, 0);
    switch (buf[1]) {
      case 0:
        digitalWrite(mf, 1);
        digitalWrite(mb, 0);
        break;
      case 1:
        digitalWrite(mf, 0);
        digitalWrite(mb, 1);
        break;
      case 2:
        digitalWrite(mf, 0);
        digitalWrite(mb, 0);
        break;
    }
  }
  byte r = push(sw);
  if (r) {
    if (r == 1) {
      digitalWrite(mf, 0);
      digitalWrite(mb, 0);
    } else if (r == 2) {
      digitalWrite(mf, 1);
      digitalWrite(mb, 0);
    } else if (r == 3) {
      digitalWrite(mf, 0);
      digitalWrite(mb, 1);
    }
  }
}

void training() {
  uint32_t t1;
  while (!digitalRead(sw)) delay(10);
  while (1) {
    if (millis() - t1 > 100) {
      t1 = millis();
      digitalWrite(led, !digitalRead(led));
    }
    byte r = push(sw);
    if (r != 0) {
      myVR.train((uint8_t)r - 1, buf);
      digitalWrite(led, 0);
      return;
    }
  }
}