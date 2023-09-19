#include "flappy.h"
#include "space.h"
#include "JRCBoard_logo.h"
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, 4);

void setup() {
  pinMode(26, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.invertDisplay(true);
  oled.clearDisplay();
  oled.drawBitmap(0, 0, JRC_Logo, 128, 64, 1);
  oled.display();



  while (digitalRead(0) && digitalRead(19))
    ;

  oled.clearDisplay();
  oled.display();

  if (!digitalRead(0)) flappy_bird();
  else if (!digitalRead(19)) space_jam();
}

void loop() {
  // put your main code here, to run repeatedly:
}
