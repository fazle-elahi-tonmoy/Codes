#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
RTCAlarmTime a1;
RTCAlarmTime a2;
#include "LedControl.h"

//this is for LED Matrix
#define data_in 10
#define cs 11
#define clk 12
#define module_count 4

//this is for push buttons and buzzer
#define menu_button 16 //this will shuffle the menu or bring back to menu
#define back_button 5
#define set_button 9 //this will engage or change a value
#define led 13 //to ensure if the button is pressed
#define lamp 3
#define long_press_timer 500 //minimum time required to register a long press
#define buzzer 2 //don't set this as same as led pin

//define how your alarm will behave
#define beeping_interval 200 //set this higher for slower alarm tone
#define return_time 30
#define menu_time 10//turn off the alarm automatically if you don't press anything in 60 seconds
uint32_t mute_timer = 60;  //set the value to 0 if you want to keep going permanently,
uint32_t snooze_time = 5;
#define maximum_snooze_count 10

//for co-ordination purpose, dont change this
int snooze_count = maximum_snooze_count;
bool snooze = 0;
byte menu_count = 1;
byte menu_limit = 2;

//this is for clock calculation
int current_time;
int current_alarm, current_alarm_2;
int current_date;
bool alarm, alarm2;
int d_time;
int hh, mm, ss, DD, MM, YY;
uint32_t m1, m2, m3, sz, al = millis();

int matrix[8];
byte one[5]   = {0x40, 0xc0, 0x40, 0x40, 0xe0};
byte two[5]   = {0xe0, 0x20, 0xe0, 0x80, 0xe0};
byte three[5] = {0xe0, 0x20, 0xe0, 0x20, 0xe0};
byte four[5]  = {0xa0, 0xa0, 0xe0, 0x20, 0x20};
byte five[5]  = {0xe0, 0x80, 0xe0, 0x20, 0xe0};
byte six[5]   = {0xe0, 0x80, 0xe0, 0xa0, 0xe0};
byte seven[5] = {0xe0, 0x20, 0x20, 0x20, 0x20};
byte eight[5] = {0xe0, 0xa0, 0xe0, 0xa0, 0xe0};
byte nine[5]  = {0xe0, 0xa0, 0xe0, 0x20, 0xe0};
byte zero[5]  = {0xe0, 0xa0, 0xa0, 0xa0, 0xe0};


LedControl lc = LedControl(data_in, clk, cs, 4);

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(menu_button, INPUT_PULLUP);
  pinMode(set_button, INPUT_PULLUP);
  pinMode(back_button, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  for (byte i = 0; i < 4; i++) {
    (i < module_count) ? lc.shutdown(i, false) : lc.shutdown(i, true);
    lc.setIntensity(i, 1); //maximum brightness is 15
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
  clock.begin();
  mute_timer = mute_timer * 1000;
  current_alarm = get_alarm();
}

void loop() {
  byte r = menu_press(0);
  if (r == 2) {
    if (!alarm) digitalWrite(lamp, !digitalRead(lamp));
      else {
        alarm = 0; digitalWrite(buzzer, 0);
        if (snooze_count > 0) {
          snooze_count --;
          snooze = 1; //alarm will snooze if menu button is pressed
          sz = millis();
        }
      }
  }
  else if (r == 1) {

  }

  r = back_press(0);
  if (r == 2) {
    if (alarm) {
      alarm = 0; digitalWrite(buzzer, 0); snooze = 0;
    }
    else {
      menu_count++;
      if (menu_count > menu_limit) menu_count = 1;
    }
    m3 = millis();
  }
  else if (r == 1) {
    lc.shutdown(3, 1); lc.shutdown(2, 1); ss = 0; alarm = 0; digitalWrite(buzzer, 0);
    while (!digitalRead(back_button));
    if (menu_count == 1) set_time();
    else if (menu_count == 2) set_alarm();
    while (!digitalRead(menu_button));
  }

  r = set_press(0);
  if (r == 1) {
    lc.shutdown(3, 1); lc.shutdown(2, 1); ss = 0; alarm = 0; digitalWrite(buzzer, 0);
    while (!digitalRead(set_button));
    if (menu_count == 1) set_time();
    else if (menu_count == 2) set_alarm();
    while (!digitalRead(menu_button));
  }
  if (r == 2) {
    alarm = 0; digitalWrite(buzzer, 0); snooze = 0;
    if (menu_count == 2) clock.armAlarm1(!clock.isArmed1());
    if (menu_count == 3) clock.armAlarm2(!clock.isArmed2());
    m3 = millis();
  }

  if (snooze && millis() - sz > snooze_time * 60000) {
    alarm = 1; //triggering the alarm
    snooze = 0;
    m2 = millis(); //for keeping the track of mute timer
  }

  if (clock.isArmed1()) {
    current_time = get_time();
    int diff =  t_diff(current_time, current_alarm);
    if (diff == 0 && ss == 0) {
      alarm = 1; //triggering the alarm
      snooze_count = maximum_snooze_count; snooze = 0;
      m2 = millis(); //for keeping the track of mute timer
    }
  }

  if (alarm) alarm_function();
  if (millis() - m3 > menu_time * 1000 && menu_count != 1) menu_count = 1;
  menu(menu_count);
}
