#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <NewPing.h>
#define sw 5
NewPing sonar(3, 2, 90);
SSD1306AsciiWire oled;
int s[6], dst;
String value;
bool mode = 0;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {
  sensor_display();
}

void text(String t, int x, int y) {
  oled.setCursor(x, y);
  oled.print(t);
}

void sensor_display() {
  oled.clear();
  while (!push(sw)) {
    for (byte i = 0; i < 6; i++) {
      (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    }
    for (byte i = 0; i < 3; i++) {
      String value = "";
      if (s[i] < 1000) value += " ";
      if (s[i] < 100) value += " ";
      if (s[i] < 10) value += " ";
      value += String(s[i]) + "  " + String(s[5 - i]) + "   ";
      text(value, 4, 6 - i * 3);
    }
  }
  oled.clear();
  while (!push(sw)) {
    dst = sonar.ping_cm();
    text(" " + String(dst) + " ", 40 + (dst < 10) * 6, 3);
    delay(100);
  }
}


byte push(byte pin) {
  byte count = 0;
  int t = 0;
  if (!digitalRead(pin)) {  //if the button is pressed
    digitalWrite(13, 1);
    delay(20);  //debounce delay
    while (!digitalRead(pin)) delay(20), t++;
    digitalWrite(13, 0);
    if (t) return 1;
  }
  return 0;
}
