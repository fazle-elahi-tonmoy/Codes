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

bool bulb_state = 0, fan_state = 0, bulb_auto = 0, security_mode = 0, theft_detect = 0, buzzer_state = 0, window_state = 0, rain_state = 0, rain_prev_state = 0;
bool setup_mode = 0, wifi_status = 0;
byte fan_speed = 255;
byte temp_speed = 0;
byte window_open = 60, window_close = 120;
uint32_t refresh_timer = 0, short_refresh = 0;
float temp;
int gas_value, hum;

static LightBulb bulb("Bulb", NULL, false);
static Switch fan("Fan", NULL, false);
static Device laser("Security", "esp.device.motion-sensor");
static Device sensor("Sensors", "esp.device.other");
static Device Window("Window", "esp.device.blinds-internal");
static TemperatureSensor temperature("Temperature", NULL, 25.0);

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

  Param gas("Gas Value", "custom.param.gasval", value(0), PROP_FLAG_READ);
  Param humidity("Humidity", "custom.param.humidity", value(75), PROP_FLAG_READ);
  Param rain("Rain Status", "custom.param.rainval", value(0), PROP_FLAG_READ);

  bulb.addPowerParam(false, "Automation");
  fan.addSpeedParam(0, "Speed");
  laser.addPowerParam(false, "Buzzer State");
  laser.addPowerParam(false, "Security Mode");
  laser.addPowerParam(false, "Theft Detection");
  Window.addPowerParam(false, "Window Closed");
  sensor.addParam(humidity);
  sensor.addParam(gas);
  sensor.addParam(rain);
  laser.addCb(write_callback);
  bulb.addCb(write_callback);
  fan.addCb(write_callback);
  Window.addCb(write_callback);
  my_node.addDevice(bulb);
  my_node.addDevice(fan);
  my_node.addDevice(laser);
  my_node.addDevice(sensor);
  my_node.addDevice(temperature);
  my_node.addDevice(Window);

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
  lcd.print("   SMART HOME   ");
  refresh_timer = millis();
  dht.begin();
}

void loop() {
  if (push(sw_alarm)) {
    if (theft_detect) {
      theft_detect = 0;
      buzzer_state = 0;
      laser.updateAndReportParam("Theft Detection", theft_detect);
      digitalWrite(buzzer, buzzer_state);
    }

    else {
      security_mode = !security_mode;
      laser.updateAndReportParam("Security Mode", security_mode);
      display_refresh();
    }
  }

  if (push(sw_light)) {
    bulb_state = !bulb_state;
    digitalWrite(bulb_pin, bulb_state);
    bulb.updateAndReportParam("Power", bulb_state);
    display_refresh();
  }

  if (push(sw_autolight)) {
    bulb_auto = !bulb_auto;
    if (!bulb_auto) digitalWrite(bulb_pin, bulb_state);
    bulb.updateAndReportParam("Automation", bulb_auto);
    display_refresh();
  }

  if (push(sw_fan)) {
    fan_state = !fan_state;
    (fan_state) ? ledcWrite(fan_channel, fan_speed) : ledcWrite(fan_channel, 0);
    fan.updateAndReportParam("Power", fan_state);
    display_refresh();
  }

  temp_speed = map(analogRead(potentiometerPin), 0, 4095, 0, 5) * 50;
  if (temp_speed != fan_speed) {
    fan_speed = temp_speed;
    (fan_state) ? ledcWrite(fan_channel, fan_speed) : ledcWrite(fan_channel, 0);
    delay(1000);
    fan.updateAndReportParam("Speed", fan_speed / 50);
    display_refresh();
  }

  if (bulb_auto && bulb_state) {
    (!digitalRead(ldr_autoPin)) ? digitalWrite(bulb_pin, 0) : digitalWrite(bulb_pin, 1);
    display_refresh();
  }

  if (security_mode) {
    if (digitalRead(ldr_laserPin) && !theft_detect) {
      theft_detect = 1;
      buzzer_state = 1;
      laser.updateAndReportParam("Theft Detection", theft_detect);
      laser.updateAndReportParam("Buzzer State", buzzer_state);
      digitalWrite(buzzer, buzzer_state);
    }
  }

  if (millis() - refresh_timer > 30000) {
    refresh_timer = millis();
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
    if (!isnan(temp)) temperature.updateAndReportParam("Temperature", temp);
    if (!isnan(hum)) sensor.updateAndReportParam("Humidity", hum);
    sensor.updateAndReportParam("Gas Value", gas_value);
  }

  rain_state = !digitalRead(rainPin);
  if (rain_state != rain_prev_state) {
    rain_prev_state = window_state = rain_state;
    (!window_state) ? window.write(window_open) : window.write(window_close);
    sensor.updateAndReportParam("Rain Status", rain_state);
    Window.updateAndReportParam("Window Closed", window_state);
  }

  if (millis() - short_refresh > 1000) {
    short_refresh = millis();
    (WiFi.status() == WL_CONNECTED) ? digitalWrite(indicator, 1) : digitalWrite(indicator, 0);
  }
  reset_protocol();
}
