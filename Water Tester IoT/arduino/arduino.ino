/* MegaLogger.ino
  Arduino Mega ADK:
  - OLED on I2C (SDA=20, SCL=21)
  - pH sensor -> A0
  - Turbidity sensor -> A1
  - NEO-6M GPS -> Serial2 (RX2/TX2)
  - DS18B20 -> digital D2
  - ESP8266 <-> Serial1 (TX1/RX1)

  Sends JSON line to ESP8266 every 15 seconds.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyGPSPlus.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pins
const int PH_PIN = A0;
const int TURBIDITY_PIN = A1;
const int ONE_WIRE_BUS = 2;  // DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
TinyGPSPlus gps;

// timers
unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 15000UL;  // 15 seconds

// calibration placeholders (you MUST calibrate for your sensors)
const float ADC_REF_VOLTAGE = 5.0;  // Mega ADC reference (default 5V)
const int ADC_MAX = 1023;

// pH calibration (example placeholders)
const float PH_VOLTAGE_AT_7 = 2.5;  // voltage reading at pH 7 (adjust)
const float PH_SLOPE = -0.17;       // pH per volt slope (adjust to your probe)

// turbidity calibration to NTU is sensor specific. We'll send raw voltage and a percent value.
float analogToVoltage(int raw) {
  return (raw * ADC_REF_VOLTAGE) / float(ADC_MAX);
}

float voltageToPH(float voltage) {
  // Simple linear conversion placeholder: pH = pH_at_7 + slope*(voltage - V_at_7)
  // You must calibrate PH_VOLTAGE_AT_7 and PH_SLOPE for your sensor
  return 7.0 + PH_SLOPE * (voltage - PH_VOLTAGE_AT_7);
}

void setup() {
  Serial.begin(115200);   // USB serial (debug)
  Serial1.begin(115200);  // to ESP8266
  Serial2.begin(9600);    // GPS (NEO-6M typically 9600)

  Wire.begin();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (1)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  sensors.begin();

  Serial.println("Mega Logger started");
}

void loop() {
  // read GPS serial into TinyGPS
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    gps.encode(c);
  }

  // read DS18B20
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if (tempC == DEVICE_DISCONNECTED_C) tempC = NAN;

  // read pH
  int phRaw = analogRead(PH_PIN);
  float phVoltage = analogToVoltage(phRaw);
  float phValue = voltageToPH(phVoltage);

  // read turbidity
  int turbRaw = analogRead(TURBIDITY_PIN);
  float turbVoltage = analogToVoltage(turbRaw);
  // convert to a 0-100% proxy for turbidity (not NTU). Calibrate separately for NTU.
  float turbPercent = map(turbRaw, 0, 1023, 0, 100);

  // get location (if available)
  double latitude = NAN;
  double longitude = NAN;
  float hdop = NAN;
  if (gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }
  if (gps.hdop.isValid()) {
    hdop = gps.hdop.hdop();
  }

  // display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("pH: ");
  if (!isnan(phValue)) {
    display.print(phValue, 2);
  } else display.print("N/A");
  display.setCursor(0, 12);
  display.print("Temp(C): ");
  if (!isnan(tempC)) display.print(tempC, 2);
  else display.print("N/A");
  display.setCursor(0, 24);
  display.print("Turb%: ");
  display.print(turbPercent, 1);
  display.setCursor(0, 36);
  if (!isnan(latitude) && !isnan(longitude)) {
    display.print("Lat:");
    display.print(latitude, 6);
    display.setCursor(0, 48);
    display.print("Lng:");
    display.print(longitude, 6);
  } else {
    display.print("GPS: No Fix");
  }
  display.display();

  // send to ESP8266 every SEND_INTERVAL
  if (millis() - lastSend >= SEND_INTERVAL) {
    lastSend = millis();
    sendDataToESP(phValue, phVoltage, phRaw, tempC, turbPercent, turbVoltage, turbRaw, latitude, longitude, hdop);
  }

  delay(200);  // small delay to allow serial events
}

void sendDataToESP(float phValue, float phVoltage, int phRaw,
                   float tempC,
                   float turbPercent, float turbVoltage, int turbRaw,
                   double lat, double lng, float hdop) {

  // Build JSON string (single line) -- ESP expects newline-terminated JSON
  String json = "{";
  json += "\"timestamp_ms\":" + String(millis());
  json += ",\"pH_value\":" + (isnan(phValue) ? String("null") : String(phValue, 3));
  json += ",\"pH_voltage\":" + String(phVoltage, 4);
  json += ",\"pH_raw\":" + String(phRaw);
  json += ",\"temp_c\":" + (isnan(tempC) ? String("null") : String(tempC, 3));
  json += ",\"turb_percent\":" + String(turbPercent, 2);
  json += ",\"turb_voltage\":" + String(turbVoltage, 4);
  json += ",\"turb_raw\":" + String(turbRaw);
  if (!isnan(lat) && !isnan(lng)) {
    json += ",\"latitude\":" + String(lat, 6);
    json += ",\"longitude\":" + String(lng, 6);
    json += ",\"hdop\":" + String(hdop, 2);
  } else {
    json += ",\"latitude\":null,\"longitude\":null";
  }
  json += "}";

  // prefix to help the ESP identify payloads (optional)
  String payload = "DATA:" + json + "\n";

  Serial.print("-> ESP: ");
  Serial.println(json);    // debug on USB
  Serial1.print(payload);  // send to ESP8266 module
}
