#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
DS3231 clock;
RTCDateTime dt;
RTCAlarmTime a1;
#include "LedControl.h"

//this is for LED Matrix
#define data_in 14
#define cs 15
#define clk 16
#define module_count 2 //for smaller display
#define brightness 1 //minimum is 1, maximum is 15

//this is for push buttons and buzzer
#define menu_button 2 //this will shuffle the menu or bring back to menu
#define set_button 12 //this will engage or change a value
#define led 13 //to ensure if the button is pressed
#define buzzer 13 //don't set this as same as led pin
#define long_press_timer 1 //minimum second pressing required to register a long press

//define how your alarm will behave
#define beeping_interval 100 //set this higher for slower alarm tone
#define return_time 30 //return to main function from blinking mode if nothing is pressed under 30 seconds 
#define menu_time 10 //return to clock display if nothing is done on alarm display after 10 seconds
uint32_t mute_timer = 60; //mutes the alarm after 60 seconds.
#define menu_button_snooze 1 //set it to 1 to snooze the alarm by pressing menu button, set button will stop alarm. if set to 0, pressing any button will stop the alarm.
uint32_t snooze_time = 5; //if nothing is pressed when alarm went off, it will ring again after 5 minutes
#define maximum_snooze_count 10
#define wait_after_alarm_setup 3 //show the alarm screen for 10 seconds if a new alarm time is set

//don't change these values below
int snooze_count = maximum_snooze_count;
bool snooze = 0; //don't change this
byte menu_count = 1;
byte menu_limit = 2; //if you want to see date also, put value 3

//this is for clock calculation
int current_time;
int current_alarm;
int current_date;
bool alarm, alarm_trigger = 0;
int hh, mm, ss, DD, MM, YY;
uint32_t m1, m2, m3, sz, al = millis();
byte pm_symbol = B11110000;
byte second_symbol_1 = B00000011;
byte second_symbol_2 = B11000000;
byte alarm_symbol = B00001111;

int matrix[8];
LedControl lc = LedControl(data_in, clk, cs, 4);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(menu_button, INPUT_PULLUP);
  pinMode(set_button, INPUT_PULLUP);
  for (byte i = 0; i < 4; i++) {
    (i < module_count) ? lc.shutdown(i, false) : lc.shutdown(i, true);
    lc.setIntensity(i, brightness); //maximum brightness is 15
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
  clock.begin();
  mute_timer = mute_timer * 1000;
  alarm_trigger = EEPROM.read(0);
  if (alarm_trigger != 0) alarm_trigger = 1;
}

void loop() {
  if (menu_press(2)) {
    if (!alarm) {
      menu_count++; m3 = millis();
      if (menu_count > menu_limit) menu_count = 1;
    }
    else {
      alarm = 0; digitalWrite(buzzer, 0);
      if (snooze_count > 0) {
        snooze_count --;
        snooze = menu_button_snooze; //alarm will snooze if menu button is pressed
        sz = millis();
      }
    }
  }

  //pressing the set button
  byte r = long_press();
  if (r == 1) {
    if (alarm) {
      alarm = 0; digitalWrite(buzzer, 0); snooze = 0;
    }
    if (menu_count == 1) {
      ss = 1; display_value(current_time);
    }
    lc.shutdown(1, 1);
    while (!digitalRead(set_button));
    if (menu_count == 1) set_time();
    if (menu_count == 2) set_alarm();
    if (menu_count == 3) set_date();
    while (!digitalRead(menu_button));
  }
  if (r == 2) {
    if (alarm) {
      alarm = 0; digitalWrite(buzzer, 0);
    }
    if (menu_count == 2) {
      alarm_trigger = !alarm_trigger;
      EEPROM.update(0, alarm_trigger);
    }
    snooze = 0; m3 = millis();
  }

  //menu display
  if (millis() - m3 > menu_time * 1000 && menu_count != 1) menu_count = 1;
  menu(menu_count); //refreshing the display

  //triggering the alarm
  if ((alarm_trigger && clock.isAlarm1()) || (snooze && millis() - sz > snooze_time * 60000)) {
    alarm = 1; //triggering the alarm
    if (!snooze) snooze_count = maximum_snooze_count;
    snooze = 0;
    m2 = millis(); //for keeping the track of mute timer
  }
  Serial.println(clock.isAlarm1());
  if (alarm) alarm_function();
}
