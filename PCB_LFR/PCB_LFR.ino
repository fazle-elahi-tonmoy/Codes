#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include<NewPing.h>
#include<EEPROM.h>
#include<Servo.h>

Servo lefthand;
Servo righthand;
SSD1306AsciiWire oled;
String value;
NewPing sonar(9, 9, 100);

#define left_motor_forward 4
#define left_motor_backward 5
#define right_motor_forward 8
#define right_motor_backward 7
#define left_motor_speed 3
#define right_motor_speed 6
#define light 13
#define spl 14 //left motor speed coeficient
#define spr 14 //right motor speed coeficient
#define swl 2
#define swr 12

//for line folloe
char flag = 's';
short int pos;
byte distance;
byte counter;
byte path[99];



short int s[6]; //this is for storing analog value of each sensor
short int thresould[] = {512, 512, 512, 512, 512, 512}; //this is the mid value for each sensor. use this array if you want to adjust midoint of each sensor individually
short int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
short int sensor; //this is to store final value after binary conversion
byte sum = 0; //this is to store the count of detected sensor
short int minimum[] = {1023, 1023, 1023, 1023, 1023, 1023};
short int maximum[] = {0, 0, 0, 0, 0, 0};
unsigned long m1, m2;


void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setInvertMode(0);
  oled.set2X();
  intro();
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(swl, INPUT_PULLUP);
  pinMode(swr, INPUT_PULLUP);
  lefthand.attach(10);
  righthand.attach(11);
  lefthand.write(90);
  righthand.write(90);

  for (byte i = 0; i < 6; i++) {
    thresould[i] = EEPROM.read(i) * 5;
    maximum[i] = EEPROM.read(i + 6) * 5;
    minimum[i] = EEPROM.read(i + 12) * 5;
  }
  for (byte i = 0; i < 99 ; i++) path[i] = EEPROM.read(i + 20);
  counter = EEPROM.read(19);
  Serial.begin(9600);
}

void loop() {
  int x = lswitch();
  if (x == 2) counter_display();
  else if (x == 1) path_select();
  x = rswitch();
  if (x == 1) {
    byte r = menu();
    if (r == 1) line_follow();
    else if (r == 2) sensordisp();
    else if (r == 3) analogReadDisp();
    else if (r == 4) {
      oled.clear(); oled.set2X(); text(" STARTING", 04, 3);
      delay(1000); motor(10 * spl, 10 * spr);
      while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH);
      while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
      motor(0, 0); intro();
    }
    else if (r == 5) bluetooth();;
  }
  else if (x == 2) callibration();
  if (Serial.available() > 0) bluetooth();
}
