#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

void setup() {
  display.begin(SSD1306_EXTERNALVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  TechTopia();
}

void loop() {
  // put your main code here, to run repeatedly:
}
