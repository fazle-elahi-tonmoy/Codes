#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include "AppInsights.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <DHT.h>
#define DHTPIN 15
#define gasPin 32
#define potentiometerPin 34
#define indicator 2
#define ldr_laserPin 27
#define ldr_autoPin 26
#define buzzer 14
#define rainPin 25
#define sw_light 18
#define sw_fan 5
#define sw_autolight 19
#define sw_alarm 23
#define fanPin 13
#define servoPin 16
#define bulb_pin 17
#define fan_channel 10

const char *service_name = "Automation";
const char *pop = "automation";

Servo window;

DHT dht(DHTPIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool bulb_state = 0, fan_state = 0, bulb_auto = 0, theft_alarm = 0, rain_state;
bool setup_mode = 0, wifi_status = 0;
byte fan_speed = 255;
byte temp_speed = 0;
byte window_open = 120, window_close = 40;
uint32_t refresh_timer = 0;
float gas_value, temp, hum;

static LightBulb bulb("Bulb", NULL, false);
static Switch fan("Fan", NULL, false);
static Switch buzz("Alarm", NULL, false);
static TemperatureSensor temparature("Temparature", NULL, 25.0);
static TemperatureSensor humidity("Humidity", NULL, 70.0);
static TemperatureSensor gas("Gas Value", NULL, 0);
static TemperatureSensor rain("Rain Status", NULL, 0);

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(ldr_autoPin, INPUT);
  pinMode(ldr_laserPin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(sw_light, INPUT_PULLUP);
  pinMode(sw_fan, INPUT_PULLUP);
  pinMode(sw_autolight, INPUT_PULLUP);
  pinMode(sw_alarm, INPUT_PULLUP);
  pinMode(bulb_pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(indicator, OUTPUT);
  window.attach(servoPin);
  window.write(window_open);
  ledcSetup(fan_channel, 1000, 8);
  ledcAttachPin(fanPin, fan_channel);
  ledcWrite(fan_channel, 0);

  Node my_node;
  my_node = RMaker.initNode("Home Automation");
  bulb.addPowerParam(false, "Automation");
  buzz.addPowerParam(false, "Security Status");
  fan.addSpeedParam(0, "Speed");
  bulb.addCb(write_callback);
  fan.addCb(write_callback);
  my_node.addDevice(bulb);
  my_node.addDevice(fan);
  my_node.addDevice(buzz);
  my_node.addDevice(temparature);
  my_node.addDevice(humidity);
  my_node.addDevice(gas);
  my_node.addDevice(rain);

  RMaker.enableOTA(OTA_USING_TOPICS);
  RMaker.enableTZService();
  RMaker.enableSchedule();
  RMaker.enableScenes();
  initAppInsights();
  RMaker.enableSystemService(SYSTEM_SERV_FLAGS_ALL, 2, 2, 2);
  RMaker.start();
  WiFi.onEvent(sysProvEvent);
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);

  lcd.init();  // initialize the lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   TECH TOPIA   ");
  refresh_timer = millis();
  dht.begin();
}

void loop() {
  if (push(sw_alarm)) {
    theft_alarm = !theft_alarm;
    if (!theft_alarm) digitalWrite(buzzer, 0);
  }

  if (push(sw_light)) {
    bulb_state = !bulb_state;
    digitalWrite(bulb_pin, bulb_state);
    bulb.updateAndReportParam("Power", bulb_state);
  }

  if (push(sw_autolight)) {
    bulb_auto = !bulb_auto;
    if (!bulb_auto) digitalWrite(bulb_pin, bulb_state);
    bulb.updateAndReportParam("Automation", bulb_auto);
  }

  if (push(sw_fan)) {
    fan_state = !fan_state;
    (fan_state) ? ledcWrite(fan_channel, fan_speed) : ledcWrite(fan_channel, 0);
    fan.updateAndReportParam("Power", fan_state);
  }

  temp_speed = map(analogRead(potentiometerPin), 0, 4095, 0, 5) * 50;
  if (temp_speed != fan_speed) {
    fan_speed = temp_speed;
    (fan_state) ? ledcWrite(fan_channel, fan_speed) : ledcWrite(fan_channel, 0);
    fan.updateAndReportParam("Speed", fan_speed / 50);
  }

  if (bulb_auto && bulb_state) {
    Serial.println(digitalRead(ldr_autoPin));
    (!digitalRead(ldr_autoPin)) ? digitalWrite(bulb_pin, 0) : digitalWrite(bulb_pin, 1);
  }

  if (theft_alarm) {
    if (digitalRead(ldr_laserPin)) digitalWrite(buzzer, 1);
  }

  if (millis() - refresh_timer > 5000) {
    refresh_timer = millis();
    rain_state = digitalRead(rainPin);
    (rain_state) ? window.write(window_open) : window.write(window_close);
    gas_value = analogRead(gasPin);
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    if (setup_mode == 0) display_refresh();
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SETUP MODE   ");
      lcd.setCursor(0, 1);
      lcd.print("  SCAN QR CODE  ");
    }
    temparature.updateAndReportParam("Temparature", (float)temp);
    humidity.updateAndReportParam("Temparature", (float)hum);
    gas.updateAndReportParam("Temparature", (float)gas_value);
    rain.updateAndReportParam("Temparature", (float)rain_state);

    (WiFi.status() == WL_CONNECTED) ? digitalWrite(indicator, 1) : digitalWrite(indicator, 0);
  }

  reset_protocol();
}
