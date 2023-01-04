#include<EEPROM.h>
#include<Servo.h>

Servo left_hand;
Servo right_hand;

byte lpos[] = {10, 90, 70};
byte rpos[] = {150, 70, 90};

#define sw 12
#define led 13
#define left_motor_forward 9
#define left_motor_backward 8
#define right_motor_forward 2
#define right_motor_backward 4
#define left_motor_speed 10
#define right_motor_speed 3
#define stby 7
#define spl 12 //left motor speed coeficient
#define spr 12 //right motor speed coeficient

#define node_delay 30
#define turn_speed 120
#define turn_brake 50
#define stop_timer 100
#define u_turn_timer 80
#define side 2
#define scan_start 50
char flag = 's';
char cross = 's';
int pos;
bool t_section = 0;
byte counter = 0;
unsigned long m1, m2;

//this is for sensors
int s[6], minimum[6], maximum[6]; //this is for storing analog value of each sensor
int thresould[6] = {333, 333, 333, 333, 333, 333}; //this is the mid value for each sensor. use this array if you want to adjust midoint of each sensor individually
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor

//this is for fixed path
byte scan[50] = {2,2,2,3,7,7,4};
//1 = left
//2 = straight
//3 = right
//4 = grab6
//5 = grab3
//6 = release
//7 = 90detect


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
  left_hand.attach(5);
  right_hand.attach(6);
  left_hand.write(10);
  right_hand.write(150);
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
    if (r == 3) motor(10 * spl, 10 * spr);
    if (r == 4) while (1) analog_value();
    if (r == 5) while (1) digital_value();
    if (r == 6) grab(1);
  }

}
