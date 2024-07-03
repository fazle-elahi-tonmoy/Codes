#define DECODE_NEC
#include "EEPROM.h"
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include "AppInsights.h"
#include "DHT.h"
#include <IRremote.hpp>
#include "IRcode.h"
DHT dht1(21, DHT11);
DHT dht2(19, DHT11);

const char *service_name = "Home Automation";
const char *pop = "automation";

bool switch_state = 0, startup = 1, power = 0, security = 0, ir_flag = 0;
uint32_t update_timer = 0, ir_timer = 0, sms_timer, prep_time, call_button, recheck_timer;
bool state[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool security_state = 0, call_b = 0, phoneCall = 0, security_check = 0;
String incoming_message;
char phone_number[15];
byte stage = 0, step = 1;

static int bulb_pins[] = { 15, 2, 4, 16, 17, 5, 18 };
static int fan_pins[] = { 13, 12, 14, 27 };
static int switch_pins[] = { 26, 25, 33, 32 };
#define IR_Remote_Pin 35
#define PIR_pin 34
#define gpio_0 0

static LightBulb bulb1("Light 1", &bulb_pins[0], false);
static LightBulb bulb2("Light 2", &bulb_pins[1], false);
static LightBulb bulb3("Light 3", &bulb_pins[2], false);
static LightBulb bulb4("Light 4", &bulb_pins[3], false);
static LightBulb bulb5("Light 5", &bulb_pins[4], false);
static LightBulb bulb6("Light 6", &bulb_pins[5], false);
static LightBulb bulb7("Light 7", &bulb_pins[6], false);
static Switch fan1("Fan 1", &fan_pins[0], false);
static Switch fan2("Fan 2", &fan_pins[1], false);
static Switch fan3("Fan 3", &fan_pins[2], false);
static Switch fan4("Fan 4", &fan_pins[3], false);
static Switch sw1("Ex 1", &switch_pins[0], false);
static Switch sw2("Ex 2", &switch_pins[1], false);
static Switch sw3("Ex 3", &switch_pins[2], false);
static Switch sw4("Ex 4", &switch_pins[3], false);
static TemperatureSensor temperature1("Inside Temperature");
static TemperatureSensor temperature2("Inside Humidity");
static TemperatureSensor temperature3("Outside Temperature");
static TemperatureSensor temperature4("Outside Humidity");
static Device trig("Security", "custom.device.security");
Node my_node;

void setup() {
  EEPROM.begin(24);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 22, 23);
  readStringFromEEPROM(1);
  Serial.println(phone_number);
  pinMode(gpio_0, INPUT_PULLUP);
  pinMode(PIR_pin, INPUT_PULLDOWN);
  for (byte i = 0; i < 7; i++) pinMode(bulb_pins[i], OUTPUT);
  for (byte i = 0; i < 4; i++) pinMode(fan_pins[i], OUTPUT);
  for (byte i = 0; i < 4; i++) pinMode(switch_pins[i], OUTPUT);

  dht1.begin();
  dht2.begin();
  IrReceiver.begin(IR_Remote_Pin, 0);

  my_node = RMaker.initNode("Bank Asia");

  Param PIR_Status("PIR Status", "custom.param.pir", value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param number("Phone Number", "esp.param.ota_status", value(phone_number), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param sms("SMS", "esp.param.ota_status", value("Type Anything Here!"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  trig.addPowerParam(false, "Security");
  trig.addPowerParam(false, "Call");
  trig.addParam(PIR_Status);
  trig.addParam(number);
  trig.addParam(sms);
  trig.assignPrimaryParam(trig.getParamByName("Security"));

  bulb1.addCb(write_callBack);
  bulb2.addCb(write_callBack);
  bulb3.addCb(write_callBack);
  bulb4.addCb(write_callBack);
  bulb5.addCb(write_callBack);
  bulb6.addCb(write_callBack);
  bulb7.addCb(write_callBack);
  fan1.addCb(write_callBack);
  fan2.addCb(write_callBack);
  fan3.addCb(write_callBack);
  fan4.addCb(write_callBack);
  sw1.addCb(write_callBack);
  sw2.addCb(write_callBack);
  sw3.addCb(write_callBack);
  sw4.addCb(write_callBack);
  trig.addCb(write_callBack);

  my_node.addDevice(trig);
  my_node.addDevice(bulb1);
  my_node.addDevice(bulb2);
  my_node.addDevice(bulb3);
  my_node.addDevice(bulb4);
  my_node.addDevice(bulb5);
  my_node.addDevice(bulb6);
  my_node.addDevice(bulb7);
  my_node.addDevice(fan1);
  my_node.addDevice(fan2);
  my_node.addDevice(fan3);
  my_node.addDevice(fan4);
  my_node.addDevice(sw1);
  my_node.addDevice(sw2);
  my_node.addDevice(sw3);
  my_node.addDevice(sw4);
  my_node.addDevice(temperature1);
  my_node.addDevice(temperature2);
  my_node.addDevice(temperature3);
  my_node.addDevice(temperature4);

  RMaker.enableOTA(OTA_USING_TOPICS);
  RMaker.enableTZService();
  RMaker.enableSchedule();
  RMaker.enableScenes();
  initAppInsights();
  RMaker.enableSystemService(SYSTEM_SERV_FLAGS_ALL, 2, 2, 2);
  RMaker.start();
  WiFi.onEvent(sysProvEvent);
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
  prep_time = millis();
}

void loop() {
  reset_protocol();

  if (startup) {
    temp_check();
    IR_Control();
    Relay_Control();
    sms_prep();
    if (stage) sendSMS(phone_number, incoming_message);

    if (phoneCall && !stage) {
      call_phone(phone_number);
      phoneCall = 0;
      call_b = 1;
      call_button = millis();
    }

    if (millis() - call_button > 1000 && call_b) {
      call_b = 0;
      trig.updateAndReportParam("Call", call_b);
    }

    if (digitalRead(PIR_pin) && security_check) {
      Serial.println("Theft Alert!");
      trig.updateAndReportParam("PIR Status", 1);
      security_check = 0;
      recheck_timer = millis();
    }

    if (!security_check && security_state && millis() - recheck_timer > 300000) {
      trig.updateAndReportParam("PIR Status", 0);
      security_check = 1;
    }
  }


  if (Serial.available())
    Serial2.write(Serial.read());

  if (Serial2.available()) {
    char x = Serial2.read();
    Serial.print(x);
  }
}
