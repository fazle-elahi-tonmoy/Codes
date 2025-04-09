#define DECODE_NEC
#include <IRremote.hpp>
#include "IRcode.h"
#include "EEPROM.h"
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include "AppInsights.h"
#include "DHT.h"

const char *service_name = "automation";
const char *pop = "automation";

DHT dht1(32, DHT11);
DHT dht2(19, DHT11);
#define IR_Remote_Pin 15
#define LDR_Pin_1 32
#define LDR_Pin_2 33
#define gpio_0 0
static int pir_pins[3] = { 27, 27, 27 };
static int ldr_pins[2] = { 27, 27 };
static int sw_pins[7] = { 13, 2, 4, 25, 26, 5, 18 };



bool state[7] = { 0, 0, 0, 0, 0, 0, 0 };
bool callB = 0, ir_flag = 0, starting = 1, security_check = 0, security_state = 0;
uint32_t ir_timer, update_timer, prep_time, sms_timer, recheck_timer;
byte step = 1, stage = 0;

int incoming_value;
String incoming_message;
String device_name, param_name;
char phone_number[11];

static Switch sw1("Switch 1", NULL, false);
static Switch sw2("Switch 2", NULL, false);
static Switch sw3("Switch 3", NULL, false);
static Switch sw4("Switch 4", NULL, false);
static Switch sw5("Switch 5", NULL, false);
static Switch sw6("Switch 6", NULL, false);
static Switch sw7("Switch 7", NULL, false);
static TemperatureSensor temperature1("Inside Temperature");
static TemperatureSensor temperature2("Inside Humidity");
static TemperatureSensor temperature3("Outside Temperature");
static TemperatureSensor temperature4("Outside Humidity");
static Device trig("Alarm", "custom.device.security");


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 17, 16);
  EEPROM.begin(256);
  delay(10);
  for (int i = 0; i < 11; i++) phone_number[i] = EEPROM.read(i + 200);

  pinMode(gpio_0, INPUT_PULLUP);
  for (byte i = 0; i < 3; i++) pinMode(pir_pins[i], INPUT_PULLDOWN);
  for (byte i = 0; i < 2; i++) pinMode(ldr_pins[i], INPUT_PULLDOWN);
  for (byte i = 0; i < 7; i++) pinMode(sw_pins[i], OUTPUT);
  IrReceiver.begin(IR_Remote_Pin, 0);
  dht1.begin();
  dht2.begin();

  Node my_node;
  my_node = RMaker.initNode("Bank Asia");

  //custom parameters
  Param trigger("Alarm Trigger", "custom.param.alarm", value((bool)0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param number("Phone Number", "esp.param.ota_status", value(phone_number), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param sms("SMS", "esp.param.ota_status", value("Type Anything Here!"), PROP_FLAG_READ | PROP_FLAG_WRITE);
  trigger.addUIType("esp.ui.trigger");
  trig.addPowerParam(false, "Security");
  trig.addParam(number);
  trig.addParam(sms);
  trig.addParam(trigger);
  trig.assignPrimaryParam(trig.getParamByName("Security"));

  sw1.addCb(write_callBack);
  sw2.addCb(write_callBack);
  sw3.addCb(write_callBack);
  sw4.addCb(write_callBack);
  sw5.addCb(write_callBack);
  sw6.addCb(write_callBack);
  sw7.addCb(write_callBack);
  trig.addCb(write_callBack);

  my_node.addDevice(trig);
  my_node.addDevice(sw1);
  my_node.addDevice(sw2);
  my_node.addDevice(sw3);
  my_node.addDevice(sw4);
  my_node.addDevice(sw5);
  my_node.addDevice(sw6);
  my_node.addDevice(sw7);
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
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
  Serial.println("Mobile Number: " + String(phone_number));
  prep_time = update_timer = millis();
}

void loop() {
  reset_protocol();
  if (starting) {
    sms_prep();
    if (callB) callBack_activate();
    if (security_state) trigger_check();
    if (stage) sendSMS();
    IR_Control();
    temp_check();

    if (Serial.available())
      Serial2.write(Serial.read());

    if (Serial2.available()) {
      char x = Serial2.read();
      Serial.print(x);
    }
  }
}
