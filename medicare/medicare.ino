#include "EEPROM.h"
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <ESP32Servo.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "DHT.h"
DHT dht(27, DHT11);
MAX30105 particleSensor;
SSD1306AsciiWire oled;
Servo drawer1, drawer2, drawer3;

const byte buzzer = 13;
const char *service_name = "Medicare";
const char *pop = "automation";

static Device draw1("Drawer 1", "esp.device.others");
static Device draw2("Drawer 2", "esp.device.others");
static Device draw3("Drawer 3", "esp.device.others");
static Device checkup("Checkup", "esp.device.others");
static Device message("Notice", "esp.device.others");
static TemperatureSensor temperature("Temparature");

byte stage = 0, step = 1;
uint32_t starting_time = 0, sms_timer, prep_time, t1 = 0, d1 = 0, d2 = 0, d3 = 0, al = 0, updt = 0, f1 = 0, f2 = 0, f3 = 0, lct = 0, draw_out_timer = 0, call_button = 0;
int interval_period, beatAvg = 60, data, s1, s2, s3, pulse_value = 0, SpO2 = 90, last_checked_time = 0;
bool b_check = 0, homepage = 1, dr1 = 0, dr2 = 0, dr3 = 0, alarm_active = 0, refresh = 0, draw_flag = 0, setup_mode = 0, phoneCall = 0, call_b = 0;
const byte min_pos = 20, max_pos = 120;
String incoming_message;
char phone_number[15];

void setup() {
  Serial.begin(115200);
  EEPROM.begin(24);
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  oled.clear();
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  dht.begin();
  pinMode(0, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);
  drawer1.attach(4);
  drawer2.attach(2);
  drawer3.attach(15);
  drawer1.write(max_pos);
  drawer2.write(max_pos);
  drawer3.write(max_pos);
  interval_period = EEPROM.read(0);
  readStringFromEEPROM(1);
  Serial.println(phone_number);
  particleSensor.begin(Wire, I2C_SPEED_FAST);
  particleSensor.setup(0x7F, 4, 3, 800, 215, 16384);
  particleSensor.enableDIETEMPRDY();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
  Node my_node;
  my_node = RMaker.initNode("Medicare Device");

  Param draw1_stat("Drawer 1 Status", "esp.param.ota_status", value("Drawer Closed"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param draw2_stat("Drawer 2 Status", "esp.param.ota_status", value("Drawer Closed"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param draw3_stat("Drawer 3 Status", "esp.param.ota_status", value("Drawer Closed"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param number("Message to", "esp.param.ota_status", value(phone_number), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param sms("SMS", "esp.param.ota_status", value("Type Anything Here!"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param alert("UPDATE", "esp.param.ota_status", value("Type Anything Here!"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param pulse_val("Pulse Value", "custom.param.pulseval", value(beatAvg), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param oxi_val("Oximeter Value", "custom.param.oxival", value(SpO2), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param interval("Interval Period", "custom.param.pstate", value(interval_period), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param last_check("Last Checked", "custom.param.pstate", value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);

  draw1.addPowerParam(false, "Drawer 1 State");
  draw1.addParam(draw1_stat);
  draw2.addPowerParam(false, "Drawer 2 State");
  draw2.addParam(draw2_stat);
  draw3.addPowerParam(false, "Drawer 3 State");
  draw3.addParam(draw3_stat);
  checkup.addPowerParam(false, "Body Check");
  checkup.addParam(pulse_val);
  checkup.addParam(oxi_val);
  checkup.addParam(interval);
  checkup.addParam(last_check);
  message.addParam(number);
  message.addPowerParam(false, "Call");
  message.addParam(sms);
  message.addParam(alert);
  // temperature.addTemperatureParam();

  draw1.addCb(write_callBack);
  draw2.addCb(write_callBack);
  draw3.addCb(write_callBack);
  checkup.addCb(write_callBack);
  temperature.addCb(write_callBack);
  message.addCb(write_callBack);

  my_node.addDevice(draw1);
  my_node.addDevice(draw2);
  my_node.addDevice(draw3);
  my_node.addDevice(checkup);
  my_node.addDevice(temperature);
  my_node.addDevice(message);

  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableSchedule();
  RMaker.enableScenes();
  RMaker.start();
  RMaker.setTimeZone("Asia/Dhaka");
  WiFi.onEvent(sysProvEvent);
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
  last_checked_time = 0;
  prep_time = lct = millis();
}

void loop() {
st:
  push_control();
  if (homepage) {
    home_screen();
    if (millis() - starting_time > 10000) {
      if (step) sms_prep();
      if (stage) sendSMS(phone_number, incoming_message);
      if (phoneCall && !stage) {
        call_phone(phone_number);
        phoneCall = 0;
        call_b = 1;
        call_button = millis();
      }
      if (millis() - call_button > 1000 && call_b) {
        call_b = 0;
        message.updateAndReportParam("Call", call_b);
      }
      alarm(alarm_active);
      drawer_update();
      if (millis() - lct > 60000) {
        lct = millis();
        last_checked_time += 1;
        checkup.updateAndReportParam("Last Checked", last_checked_time);
        float t = dht.readTemperature();
        temperature.updateAndReportParam("Temperature", t);
      }
      if (last_checked_time >= interval_period && interval_period > 0) b_check = true;
      if (b_check) full_checkup();


      if (alarm_active) {
        refresh = 1;
        t1 = millis();
      }

      if (Serial2.available()) {
        char c = Serial2.read();
        Serial.print(c);
      }

      if (Serial.available()) {
        char c = Serial.read();
        Serial2.print(c);
      }
    }
  } 
  
  else {
    setup_mode = 1;
    last_checked_time = 0;
    prep_time = lct = starting_time = millis();
  }
}
