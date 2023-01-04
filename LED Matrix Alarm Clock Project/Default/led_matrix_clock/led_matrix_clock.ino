#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
#include "LedControl.h"

//this is for LED Matrix
#define data_in 16
#define clk 14
#define cs 15
#define module_count 2

//this is for push buttons
#define menu_button 2
#define set_button 12
#define led 13 //to ensure if the button is pressed
#define long_press_timer 500

//for co-ordination purpose, dont change this
byte menu_count = 1;
bool stability = 1;
byte menu_limit = 2;

//this is for clock calculation
int current_time;
int current_date;
int clock_time;
int hh, mm, ss, DD, MM, YY;
uint32_t m1, m2, m3;

int matrix[8];
LedControl lc = LedControl(data_in, clk, cs, 4);
void setup() {
  pinMode(menu_button, INPUT_PULLUP);
  pinMode(set_button, INPUT_PULLUP);
  for (byte i = 0; i < 4; i++) {
    (i < module_count) ? lc.shutdown(i, false) : lc.shutdown(i, true);
    lc.setIntensity(i, 1); //maximum brightness is 15
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
  clock.begin();
  // Manual (YYYY, MM, DD, HH, II, SS)
  // clock.setDateTime(2014, 4, 13, 19, 21, 00);

}

void loop() {
  if (menu_press(2)) {
    menu_count++; stability = 1;
    if (menu_count > menu_limit) menu_count = 1;
  }
  if (set_press(0) == 1) {
    lc.shutdown(1, 1);
    while (!digitalRead(set_button));
    if (menu_count == 1) set_time();
    while (!digitalRead(menu_button));
  }
  menu(menu_count);
  Serial.println(ss%2);
}
