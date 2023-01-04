#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
RTCAlarmTime a1;
#include "LedControl.h"

//this is for LED Matrix
#define data_in 14
#define clk 16
#define cs 15
#define module_count 2 //for smaller display

//this is for push buttons and buzzer
#define menu_button 11 //this will shuffle the menu or bring back to menu
#define set_button 7 //this will engage or change a value
#define led 13 //to ensure if the button is pressed
#define long_press_timer 500 //minimum time required to register a long press
#define buzzer 2 //don't set this as same as led pin

//define how your alarm will behave
#define beeping_interval 100 //set this higher for slower alarm tone
//turn off the alarm automatically if you don't press anything in 60 seconds
#define mute_timer 60  //set the value to 0 if you want to keep going permanently, 

//for co-ordination purpose, dont change this
byte menu_count = 1;
byte menu_limit = 2; //if you want to see date also, put value 3

//this is for clock calculation
int current_time;
int current_alarm;
int current_date;
bool alarm;
int hh, mm, ss, DD, MM, YY;
uint32_t m1, m2, al = millis();

int matrix[8];
LedControl lc = LedControl(data_in, clk, cs, 4);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(menu_button, INPUT_PULLUP);
  pinMode(set_button, INPUT_PULLUP);
  for (byte i = 0; i < 4; i++) {
    (i < module_count) ? lc.shutdown(i, false) : lc.shutdown(i, true);
    lc.setIntensity(i, 1); //maximum brightness is 15
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
  clock.begin();

}

void loop() {
  if (menu_press(2)) {
    if (!alarm) {
      menu_count++;
      if (menu_count > menu_limit) menu_count = 1;
    }
    alarm = 0; digitalWrite(buzzer, 0);
  }
  byte r = set_press(0);
  if (r == 1) {
    lc.shutdown(1, 1); alarm = 0; digitalWrite(buzzer, 0);
    while (!digitalRead(set_button));
    if (menu_count == 1) set_time();
    if (menu_count == 2) set_alarm();
    if (menu_count == 3) set_date();
    while (!digitalRead(menu_button));
  }
  if (r == 2) {
    alarm = 0; digitalWrite(buzzer, 0);
    if (menu_count == 2) clock.armAlarm1(!clock.isArmed1());
  }
  menu(menu_count); //refreshing the display
  if (clock.isAlarm1()){
    alarm = 1; //triggering the alarm
    m2 = millis(); //for keeping the track of snooze timer
  }
  if (alarm) alarm_function();
}
