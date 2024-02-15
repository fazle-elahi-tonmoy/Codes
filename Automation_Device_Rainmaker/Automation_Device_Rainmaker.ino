#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire oled;

const char *service_name = "Automation Device";
const char *pop = "automation";

static int lbutton = 18;
static int rbutton = 05;
static int reset_button = 00;
static int long_press_timer = 1000;
static int bulb_switch = 32;
static int socket_switch = 33;
bool bulb_state = false;
bool socket_state = false;
bool bulb_timer = false;
bool socket_timer = false;
bool homepage = true;
bool signboard = false;
static Device socket("Socket", "esp.device.outlet", &socket_switch);
static Device sign("Sign Board", "esp.device.others");
static LightBulb bulb("Light", &bulb_switch, false);
int bulb_time, socket_time;
uint32_t t, t2;


void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  oled.clear();
  Serial.begin(115200);

  pinMode(lbutton, INPUT_PULLUP);
  pinMode(rbutton, INPUT_PULLUP);
  pinMode(reset_button, INPUT_PULLUP);
  pinMode(bulb_switch, OUTPUT);
  pinMode(socket_switch, OUTPUT);
  digitalWrite(bulb_switch, 1);
  digitalWrite(socket_switch, 0);

  Node my_node;
  my_node = RMaker.initNode("ESP RainMaker Node");

  //adding custom parameter
  Param time_param1("Bulb Timer", "custom.param.timer1", value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param time_param2("Socket Timer", "custom.param.timer2", value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  Param signal("Notice", "esp.param.ota_status", value("Put Your Notice Here!"), PROP_FLAG_READ | PROP_FLAG_WRITE);


  socket.addNameParam();
  socket.addPowerParam(false);
  socket.addPowerParam(false, "Timer Activation");
  socket.addParam(time_param2);
  socket.assignPrimaryParam(socket.getParamByName(ESP_RMAKER_DEF_POWER_NAME));

  bulb.addPowerParam(false, "Timer Activation");
  bulb.addParam(time_param1);

  sign.addParam(signal);

  bulb.addCb(write_callBack);
  socket.addCb(write_callBack);
  sign.addCb(write_callBack);
  my_node.addDevice(bulb);
  my_node.addDevice(socket);
  my_node.addDevice(sign);

  //This is optional
  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.setTimeZone("Asia/Dhaka");
  RMaker.enableSchedule();
  RMaker.enableScenes();
  RMaker.start();

  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.setTimeZone("Asia/Dhaka");
  WiFi.onEvent(sysProvEvent);
  // WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
  configTime(21600, 0, "asia.pool.ntp.org");
  t = t2 = millis();
}

void loop() {
  int r = press(lbutton);
  if (r && signboard) {
    signboard = 0;
    sign.updateAndReportParam("Notice", "Notice Seen");
    oled.clear();
  }

  else if (r == 1) {
    bulb_state = !bulb_state;
    bulb.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, bulb_state);
    digitalWrite(bulb_switch, !bulb_state);
  }

  else if (r == 2) set_timer(1);

  r = press(rbutton);
  if (r && signboard) {
    signboard = 0;
    sign.updateAndReportParam("Notice", "Notice Seen");
    oled.clear();
  }

  else if (r == 1) {
    socket_state = !socket_state;
    socket.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, socket_state);
    digitalWrite(socket_switch, socket_state);
  }

  else if (r == 2) set_timer(2);

  reset_protocol();
  home_screen();


  if (bulb_timer && bulb_time == 0) {
    bulb_timer = 0;
    bulb_state = !bulb_state;
    bulb.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, bulb_state);
    timer_parameter_update();
    digitalWrite(bulb_switch, !bulb_state);
  }

  if (socket_timer && socket_time == 0) {
    socket_timer = 0;
    socket_state = !socket_state;
    socket.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, socket_state);
    timer_parameter_update();
    digitalWrite(socket_switch, socket_state);
  }

  if (millis() - t > 60000) {
    t = millis();
    if (bulb_timer && bulb_time > 0) bulb_time -= 1;
    if (socket_timer && socket_time > 0) socket_time -= 1;
    timer_parameter_update();
  }
}
