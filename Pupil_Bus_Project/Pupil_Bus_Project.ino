#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <BluetoothSerial.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "bitmap.h"
MFRC522 rfid(5, 4);  //SDA PIN, RST PIN
Adafruit_SSD1306 display(128, 64, &Wire, -1);
HardwareSerial gpsSerial(2);
BluetoothSerial SerialBT;
TinyGPSPlus gps;

const char *ssid = "JRC Board";
const char *password = "robotics";

String vehicle1_id = "64e5e40dcac0cd65d975e905";
String vehicle2_id = "64e73b24d822511bc400ea05";
String vehicle_id = vehicle1_id;
String gps_location;

uint32_t t1, t2;
const byte led = 2, button = 0, buzzer = 13;
bool vehicle_state = 0, gps_connected = 1, debugging_mode = 0;
byte cardValue[4];
String rfid_value = "", jsonData, latitude, longitude;
float lat, lng;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
  Serial.begin(115200);
  gpsSerial.begin(9600);
  WiFi.begin(ssid, password);
  text("CONNECTING", 04, 25, 2);
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  configTime(21600, 0, "asia.pool.ntp.org");
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  if (millis() - t1 > 10000) {
    t1 = millis();
    if (gps_connected) {
      gps_location = latitude + ", " + longitude;
      sendPutRequest(vehicle_id, gps_location);
    }
  }

  if (millis() - t2 > 1000) {
    t2 = millis();
    gps_read();
    if (debugging_mode) debug_display();
    starting_screen();
  }

  rfid_check();
  push_function();
}
