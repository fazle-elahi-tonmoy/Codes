#include <WiFi.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>
WiFiManager wm;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  wm.autoConnect("WiFi Setup");

  ArduinoOTA.setHostname("Tech Topia");
  ArduinoOTA.setPassword("robotics");
  ArduinoOTA.begin();

  pinMode(0, INPUT_PULLUP);
}

void loop() {
  ArduinoOTA.handle();
  reset_protocol();
}

void reset_protocol() {
  if (!digitalRead(0)) {
    uint32_t timer = 0;
    while (!digitalRead(0)) {
      Serial.print(" . ");
      delay(1000);
    }
    Serial.println();
    if (millis() - timer > 5000) {
      wm.resetSettings();
      wm.autoConnect("WiFi Setup");
    }
  }
}