#include<EEPROM.h>
#define sw 12
#define led 13
#define left_motor_speed 5
#define left_motor_forward 6
#define left_motor_backward 7
#define right_motor_forward 9
#define right_motor_backward 8
#define right_motor_speed 10
#define stby 7
#define spl 12 //left motor speed coeficient
#define spr 12 //right motor speed coeficient

#define node_delay 30
#define turn_speed 120
#define turn_brake 50
#define stop_timer 100
#define u_turn_timer 80
#define side 0
#define scan_start 50
char flag = 's';
char cross = 's';
int pos;
byte scan[50] = {};
byte counter = 0;
unsigned long m1, m2;

//this is for sensors
int s[6], minimum[6], maximum[6]; //this is for storing analog value of each sensor
int thresould[6] = {333, 333, 333, 333, 333, 333}; //this is the mid value for each sensor. use this array if you want to adjust midoint of each sensor individually
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor


void setup() {

  pinMode (sw, INPUT_PULLUP);
  pinMode (led, OUTPUT);
  pinMode (11, OUTPUT);
  digitalWrite(11, LOW);
  Serial.begin (9600);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH);
  for (int i = 0; i < 6; i++) {
    minimum[i] = EEPROM.read(i) * 4;
    thresould[i] = EEPROM.read(i + 6) * 4;
    maximum[i] = EEPROM.read(i + 12) * 4;
    Serial.println(String(minimum[i]) + " " + String(thresould[i]) + " " + String(maximum[i]));
  }

}

void loop() {


  int r = button();
  if (r != 0) {
    if (r == 1) fixed_path();
    if (r == 2) callibration();
    if (r == 3) maze_scan(0);
    if (r == 4) maze_scan(1);
    if (r == 5) maze_solve(0);
    if (r == 6) maze_solve(1);
    if (r == 7) motor(10 * spl, 10 * spr);
    if (r == 8) while (1) analog_value();
    if (r == 9) while (1) digital_value();
    if (r == 10) memory_recall();
  }

}
