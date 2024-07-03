#include "bitmap.h"
#include "WiFi.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
int frame = 0;
uint32_t timer = millis();
uint32_t refresh = millis();

String WiFi1 = "RBTECH BD";
String WiFi2 = "Risat";
String WiFi3 = "Rubel wifi";

bool home = 1;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 17, 5);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(1);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() {
  int r = push(0);
  if (r) {
    if (r == 1) {
      display.clearDisplay();
      display.setCursor(4, 24);
      display.print(" SCANNING ");
      display.display();
      WiFi_scan();
    }
  }
  if (home) home_screen();
  if (millis() - refresh > 5000) home = 1;

  if (Serial1.available()) {
    char x = Serial1.read();
    Serial.write(x);
    if (x == 'S') WiFi_scan();
    if (x == 'F') {
      display.clearDisplay();
      display.setCursor(4, 24);
      display.print(" STARTED! ");
      display.display();
      home = 0;
      refresh = millis();
    }
    if (x == 'I') {
      display.clearDisplay();
      display.setCursor(4, 24);
      display.print(" FINISHED ");
      display.display();
      home = 0;
      refresh = millis();
    }
  }
}
