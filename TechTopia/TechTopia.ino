#include <Adafruit_SSD1306.h>
#include <Wire.h>
Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  // display.setRotation(1);
  // TechTopia();
  display.setCursor(0, 0);
  display.print("HELLO");
}

void loop() {
  // put your main code here, to run repeatedly:
}
