#include<EEPROM.h>
#include<SoftwareSerial.h>
SoftwareSerial bt(2, 3);

#define left_motor_speed 5
#define left_motor_forward 7
#define left_motor_backward 6
#define stby 8
#define right_motor_forward 9
#define right_motor_backward 10
#define right_motor_speed 11
#define head_light 13
#define red_light 4
#define sw 12


#define spl 16 //left motor speed coeficient
#define spr 16 //right motor speed coeficient
#define dr 3 // hardness of straightner
#define tsp 150
#define tbr 30
#define side 2
#define turn_delay 40
#define node_delay 80
#define stop_timer 120
#define u_turn_timer 120
#define return_delay 550
#define brake 20
int maximum[6], minimum[6], mid[6];
char flag = 's';
int pos;



int s[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor
unsigned long m1, m2, m3;
byte scan[50];
byte counter = 0;
byte cross = 0;

void setup() {
  Serial.begin(9600);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(head_light, OUTPUT);
  pinMode(red_light, OUTPUT);
  digitalWrite(stby, 1);
  pinMode(sw, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 5;
    maximum[i] = EEPROM.read(i + 6) * 5;
    minimum[i] = EEPROM.read(i + 12) * 5;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
}

void loop() {
  int r = push();
  if (r != 0) {
    if (r == 1) line_follow();
    else if (r == 2) {
      r = 0; delay(500);
      while (r == 0) {
        r = push();
        if (millis() - m2 > 200) {
          m2 = millis();
          digitalWrite(head_light, !digitalRead(head_light));
        }
        if (r == 1) maze_scan(0);
        else if (r == 2) maze_scan(1);
      }
    }
    else if (r == 3) {
      r = 0; delay(500);
      while (r == 0) {
        r = push();
        if (millis() - m2 > 200) {
          m2 = millis();
          digitalWrite(head_light, !digitalRead(head_light));
        }
        if (r == 1) maze_solve(0);
        else if (r == 2) maze_solve(1);
      }
    }
    else if (r == 4) cal();
    else if (r == 5) bluetooth_control();
    else if (r == 6) {
      r = 0; delay(500);
      while (r == 0) {
        r = push();
        if (millis() - m2 > 200) {
          m2 = millis();
          digitalWrite(head_light, !digitalRead(head_light));
        }
        if (r == 1) while (digitalRead(sw)) digital_value();
        else if (r == 2) while (digitalRead(sw)) analog_value();
        else if (r == 3) while (digitalRead(sw)) motor(10 * spl, 10 * spr);
        else if (r == 4) {
          motor(-100, 100); delay(return_delay);
          motor(100, -100); delay(tbr); motor(0, 0);
        }
      }
    }
    else if (r == 7) for (int i = 0; i <= EEPROM.read(19); i++) Serial.println(EEPROM.read(i + 20));
    motor(0, 0); digitalWrite(head_light, 0);  digitalWrite(red_light, 0); while (!digitalRead(sw));
  } 
  if (bt.available()) bluetooth_control();
}
