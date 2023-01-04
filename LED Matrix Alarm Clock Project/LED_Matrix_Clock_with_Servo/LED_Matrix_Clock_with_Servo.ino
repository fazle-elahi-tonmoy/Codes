#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
#include<Servo.h>
#include<DHT.h>
#include <LedControl.h>
Servo servo1;
Servo servo2;
DS3231 clock;
RTCDateTime dt;
RTCAlarmTime a1;
RTCAlarmTime a2;

//this is for DHT11
#define DHTPIN A3 // Digital pin connected to the DHT sensor
int t, f, h; //for storing data. don't touch these.
uint32_t temp_interval = 2; //wait for at least 2 second to update the next reading.
int dht_timer = 7; // return to main menu from temparature display if nothing is pressed for 7 seconds

//this is for LED Matrix
#define data_in 14
#define cs 15
#define clk 16
#define module_count 2 //for smaller display
#define brightness 1 //minimum is 1, maximum is 15

//this is for servo motors
#define servo1_pin 9 //Servo 1 signal is connected on this pin
#define servo2_pin 10 //Servo 2 signal is connected on this pin
#define servo_button 12 //this button will control Servo 1 position
int servo1_stat, servo2_stat; //this is to track the position of servo motors
byte s1_phase, s2_phase; //this is to track the progress of the servo motors

//for servo motor 1
int servo1_pos[] = {150, 80, 0}; //servo1 position from left to right
int servo1_left_rotation_speed = 90; //100 percent means maximum, minimum is 0
int servo1_left_to_mid_rotation_speed = 90; //100 percent means maximum, minimum is 0
int servo1_right_rotation_speed = 90; //100 percent means maximum, minimum is 0
int servo1_right_to_mid_rotation_speed = 90; //100 percent means maximum, minimum is 0
int servo1_left_waiting_time = 3;//wait in the left position for 3 seconds before moving again
int servo1_mid_waiting_time = 3; //wait in the mid position for 3 seconds before moving again
int servo1_right_waiting_time = 3; //wait in the right position for 3 seconds before moving again

//for servo to motor 2
int servo2_pos[] = {90, 45, 0}; //servo2 position from left to right
int servo2_left_rotation_speed = 70; //100 percent means maximum, minimum is 0
int servo2_left_to_mid_rotation_speed = 70; //100 percent means maximum, minimum is 0
int servo2_right_rotation_speed = 70; //100 percent means maximum, minimum is 0
int servo2_right_to_mid_rotation_speed = 70; //100 percent means maximum, minimum is 0
int servo2_left_waiting_time = 3;//wait in the left position for 3 seconds before moving again
int servo2_mid_waiting_time = 3; //wait in the mid position for 3 seconds before moving again
int servo2_right_waiting_time = 3; //wait in the right position for 3 seconds before moving again

//this is for push buttons and buzzer
#define menu_button 6 //this will shuffle the menu or bring back to menu
#define set_button 11 //this will engage or change a value
#define special_button 8 //this will bring to the second alarm menu
#define temp_button 2 // this will bring to temparature display
#define warning_led_1 4 //this will turn on if the actual time is past the starting time of second alarm
#define warning_led_2 3 //this will turn on if there remains less than 20 minutes for second alarm
#define warning_led_3 5 //this will turn on if the second alarm is triggered
#define alarm_2_display_led 7 //this will indicate if your second alarm is turned on or armed
#define buzzer 13 //alarm sound indicator
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
int s_alarm_1;
int s_alarm_2;
int current_date;
int d_time;
bool alarm;
int hh, mm, ss, DD, MM, YY;
uint32_t m1, m2, m3, sz, al = millis(), tm = millis(), ms1, ms2, dh;
byte pm_symbol = B11110000;
byte second_symbol_1 = B00000011;
byte second_symbol_2 = B11000000;
byte alarm_symbol = B00001111;
int matrix[8];
byte celcius[8] = {0x00, 0x60, 0x6e, 0x08, 0x08, 0x08, 0x0e, 0x00};
byte farenhite[8] = {0x00, 0x60, 0x6e, 0x08, 0x0e, 0x08, 0x08, 0x00};
byte percentage[8] = {0x00, 0x32, 0x34, 0x08, 0x10, 0x2c, 0x4c, 0x00};


LedControl lc = LedControl(data_in, clk, cs, 4);
DHT dht(DHTPIN, DHT11);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(menu_button, INPUT_PULLUP);
  pinMode(set_button, INPUT_PULLUP);
  pinMode(special_button, INPUT_PULLUP);
  pinMode(temp_button, INPUT_PULLUP);
  pinMode(servo_button, INPUT_PULLUP);
  pinMode(warning_led_1, OUTPUT);
  pinMode(warning_led_2, OUTPUT);
  pinMode(warning_led_3, OUTPUT);
  pinMode(alarm_2_display_led, OUTPUT);
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo1.write(servo1_pos[1]); //Servo 1 middle position
  servo2.write(servo2_pos[1]); //Servo 2 middle position
  for (byte i = 0; i < 4; i++) {
    (i < module_count) ? lc.shutdown(i, false) : lc.shutdown(i, true);
    lc.setIntensity(i, brightness); //maximum brightness is 15
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
  dht.begin();
  clock.begin();
  mute_timer = mute_timer * 1000;
  current_alarm = get_alarm();
  s_alarm_1 = get_initial();
  s_alarm_2 = get_alarm_2();
}

void loop() {
  if (menu_press(2)) {
    if (!alarm) {
      menu_count++; m3 = millis();
      if (menu_count > menu_limit) menu_count = 1;
    }
    else {
      alarm = 0; digitalWrite(buzzer, 0); digitalWrite(warning_led_3, LOW);
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
      alarm = 0; digitalWrite(buzzer, 0); snooze = 0; digitalWrite(warning_led_3, LOW);
    }
    if (menu_count == 1) {
      ss = 1; clock_update();
    }
    lc.shutdown(1, 1);
    while (!digitalRead(set_button));
    if (menu_count == 1) set_time();
    else if (menu_count == 2) set_alarm();
    else if (menu_count == 3) set_date();
    else if (menu_count == 4) set_start_time();
    else if (menu_count == 5)set_alarm2();
    while (!digitalRead(menu_button));
  }
  else if (r == 2) { //short press to trigger alarm or go to DHT11 display
    if (alarm) {
      alarm = 0; digitalWrite(buzzer, 0); digitalWrite(warning_led_3, LOW);
    }
    if (menu_count == 2) clock.armAlarm1(!clock.isArmed1());
    if (menu_count == 5 || menu_count == 4) {
      clock.armAlarm2(!clock.isArmed2());
      digitalWrite(warning_led_1, LOW);
      digitalWrite(warning_led_2, LOW);
      digitalWrite(warning_led_3, LOW);
    }
    snooze = 0; m3 = millis();
  }
  else if (special_press()) {
    if (menu_count == 4) menu_count = 5;
    else if (menu_count == 5) menu_count = 1;
    else menu_count = 4;
    m3 = millis();
  }
  else if (temp_press()) {
    if (menu_count == 6) menu_count = 7;
    else if (menu_count == 7) menu_count = 8;
    else menu_count = 6;
    dh = millis();
  }
  else if (servo_press()) servo_move();

  //snooze alarm
  if (snooze && millis() - sz > snooze_time * 60000) {
    alarm = 1; //triggering the alarm
    snooze = 0;
    m2 = millis(); //for keeping the track of mute timer
  }

  //triggering the alarm
  if (clock.isArmed1()) {
    current_time = get_time();
    int diff =  t_diff(current_time, current_alarm);
    if (diff == 0 && ss == 0) {
      alarm = 1; //triggering the alarm
      snooze_count = maximum_snooze_count; snooze = 0;
      m2 = millis(); //for keeping the track of mute timer
    }
  }
  if (clock.isArmed2()) {
    d_time = t_diff(s_alarm_2, s_alarm_1); current_time = get_time();
    int start_diff = t_diff(current_time, s_alarm_1);
    int end_diff = t_diff(s_alarm_2, current_time);
    (start_diff < d_time && end_diff >= 20) ? digitalWrite(warning_led_1, HIGH) : digitalWrite(warning_led_1, LOW);
    (end_diff < 20 && end_diff > 0) ? digitalWrite(warning_led_2, HIGH) : digitalWrite(warning_led_2, LOW);
    if (end_diff != 0) digitalWrite(warning_led_3, LOW);
    if (end_diff == 0 && ss == 0) {
      alarm = 1; //triggering the alarm
      snooze_count = maximum_snooze_count; snooze = 0; digitalWrite(warning_led_3, HIGH);
      m2 = millis(); //for keeping the track of mute timer
    }
  }
  Serial.println(String(clock.isArmed1()));
  if (alarm) alarm_function();

  temp_update();

  if (millis() - m3 > menu_time * 1000 && menu_count > 1 && menu_count < 6) menu_count = 1;
  if (millis() - dh > dht_timer * 1000 && menu_count >= 6) menu_count = 1;
  menu(menu_count); //refreshing the display
}
