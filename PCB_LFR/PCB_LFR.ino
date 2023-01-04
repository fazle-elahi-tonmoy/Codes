#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <NewPing.h>
#include <EEPROM.h>
#include <Servo.h>

Servo lefthand;
Servo righthand;
SSD1306AsciiWire oled;
String value;
NewPing sonar(9, 9, 20);

#define left_motor_forward 5
#define left_motor_backward 4
#define right_motor_forward 8
#define right_motor_backward 7
#define left_motor_speed 3
#define right_motor_speed 6
#define light 13
#define swl 8
#define swr 7

//for line follow
byte sp, spl, spr, le, re, br, tbr, tsp, flag, node, cross, distance, counter, path[50], epoint, dt, turn, dis;
short int pos;
byte lservo[3] = { 150, 70, 50 };
byte rservo[3] = { 30, 110, 130 };
unsigned long m1, m2, m3;




short int s[6];                                            //this is for storing analog value of each sensor
short int thresould[] = { 512, 512, 512, 512, 512, 512 };  //this is the mid value for each sensor. use this array if you want to adjust midoint of each sensor individually
short int base[6] = { 1, 2, 4, 8, 16, 32 };                //this is for binary to decimal conversion
short int sensor;                                          //this is to store final value after binary conversion
byte sum = 0;                                              //this is to store the count of detected sensor
short int minimum[] = { 1023, 1023, 1023, 1023, 1023, 1023 };
short int maximum[] = { 0, 0, 0, 0, 0, 0 };


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
  righthand.attach(9);
  lefthand.write(lservo[0]);
  righthand.write(rservo[0]);

  for (byte i = 0; i < 6; i++) {
    thresould[i] = EEPROM.read(i) * 5;
    maximum[i] = EEPROM.read(i + 6) * 5;
    minimum[i] = EEPROM.read(i + 12) * 5;
  }
  sp = EEPROM.read(18);
  le = EEPROM.read(19);
  re = EEPROM.read(20);
  dt = EEPROM.read(21);
  br = EEPROM.read(22);
  tbr = EEPROM.read(23);
  tsp = EEPROM.read(24);
  node = EEPROM.read(25);
  epoint = EEPROM.read(26);
  turn = EEPROM.read(27);
  spl = sp - le;
  spr = sp - re;
  counter = EEPROM.read(29);
  for (byte i = 0; i < 49; i++) path[i] = EEPROM.read(i + 30);
  Serial.begin(9600);
}

void loop() {
  byte x = lswitch();
  if (x == 2) counter_display();
  else if (x == 1) path_select();

  x = rswitch();
  if (x == 1) {
    byte r = menu();
    if (r == 1) adjustment_menu();
    else if (r == 2) callibration();
    else if (r == 3) sensordisp();
    else if (r == 4) analogReadDisp();
    else if (r == 5) {
      oled.clear();
      oled.set2X();
      text(" STARTING", 04, 3);
      delay(1000);
      motor(10 * spl, 10 * spr);
      while (digitalRead(swl) == HIGH && digitalRead(swr) == HIGH)
        ;
      while (digitalRead(swl) == LOW || digitalRead(swr) == LOW)
        ;
      motor(0, 0);
      intro();
    }

    else if (r == 6) bluetooth();
    else if (r == 7) servo_test();
    else if (r == 8) {
      oled.clear();
      oled.set2X();
      text(" STARTING", 04, 3);
      delay(1000);
      motor(-80, 80);
      delay(turn * 5);
      motor(0, 0);
      intro();
    }
  }

  else if (x == 2) line_follow();
  if (Serial.available() > 0) bluetooth();
}
