#include<EEPROM.h>
#include<Servo.h>
#include<NewPing.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

//for servo control
Servo handle;
Servo grab;
int hpos, gpos;

//for sonar sensor
#define trl 42
#define trf 40
#define trr 38
int sf = 0, sl = 0, sr = 0;
int object_boundary = 15, wall_boundary = 15, midpoint = 12, turn = 350, error = 0, wallp = 0;

NewPing sonarl(trl, trl, 90);
NewPing sonarf(trf, trf, 90);
NewPing sonarr(trr, trr, 90);

//for colour sensor
#define s0 36
#define s1 34
#define s2 32
#define s3 30
#define out 28

// for motor driver
#define lmf 2
#define lmb 3
#define rmf 5
#define rmb 4

//for line follow
int sp = 25;
int spe = 0;
int btd = 60;
int mtd = 200;
int ltd = 60;
int rtd = 0;
int tsp = 200;
#define dt 10
int br = 60;
int k = 0;
int base = 40;
int peak = 160;
int cl = base;
int d = 2;
int brake = cl / d;
int counter = 0;
int tcount = 0;
int mode = 1;
int side = 0;

//for 30degeree & 90 degree && other logic
int k30 = 0;
int k90 = 0;
int mov = 0;
int cross = 0;
unsigned long mi1 = 0, mi2 = 0, mi3 = 0, mi4 = 0, m81 = 0, m82 = 0 ;


//for ir sensor logic
int bin = 0;
int sum = 0;
int sensor[] = { 0, 0, 0, 0, 0, 0};
int bina[] = {1, 2, 4, 8, 16, 32};

//for calibration & store
#define swl 22
#define swr 24
int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
int maximum[] = {0, 0, 0, 0, 0, 0};
int trash[] = {0, 0, 0, 0, 0, 0};
float cal_p = 0.5;

//for debug light
#define red 9
#define green 11
#define blue 13
#define light 44




void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(swl, INPUT_PULLUP);
  pinMode(swr , INPUT_PULLUP);
  pinMode(light, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A15, OUTPUT);
  digitalWrite(A11, LOW);
  digitalWrite(A15, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  mos(0, 0);

  for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;

  sp = EEPROM.read(6);
  spe = EEPROM.read(7)-128;
  hpos = EEPROM.read(8);
  gpos = EEPROM.read(9);
  counter = EEPROM.read(10);
  turn = EEPROM.read(11) * 5;
  mtd = EEPROM.read(12);
  rtd = EEPROM.read(13);
  ltd = EEPROM.read(14);
  tsp = EEPROM.read(15);
  br = EEPROM.read(16);
  d = EEPROM.read(17);
  base = EEPROM.read(18) * d;
  peak = EEPROM.read(19) * d;
  cl = base;
  brake = cl / d;
  side = EEPROM.read(20);
  object_boundary = EEPROM.read(21);
  wall_boundary = EEPROM.read(22);
  midpoint = EEPROM.read(23);
  wallp = EEPROM.read(24);
  cal_p = EEPROM.read(25) * 0.1;
  Serial.begin(9600);
  sust_cracker_nut();

}


void loop()
{
  int r = 0;
  r = menu_function1();
  if (r != 0) {
    if (r == 1) {
      if (mode == 0) {
        display.clearDisplay();
        text(" REVERSE ", 10, 24);
        display.display();
      }
      delay(200);
      line_follow();
      motorSpeedS();
    }
    else if (r == 2) {
      text_callibrating();
      for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
    }
    else if (r == 3) {
      while (digitalRead(swl) == HIGH) analog_reading_display();
    }
    else if (r == 4) {
      while (digitalRead(swl) == HIGH) digital_reading_display();
    }
    else if (r == 5) {
      while (digitalRead(swl) == HIGH) sonar_reading_display();
    }
    else if (r == 6) {
      digitalWrite(light, HIGH);
      while (digitalRead(swl) == HIGH) {
        display.clearDisplay();
        char c = colour();
        if (c == 'r') text("   RED   ", 10, 16);
        else if (c == 'g') text("  GREEN  ", 10, 16);
        else if (c == 'b') text("   BLUE   ", 4, 16);
        display.display();
      }
      digitalWrite(light, LOW);
    }
    else if (r == 7) {
      display.clearDisplay();
      text("STARTING..", 04, 24);
      display.display();
      delay(1000);
      while (digitalRead(swl) == HIGH) mos(10 * sp, 10 * sp);
      mos(0, 0);
    }
    sust_cracker_nut();
    while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
  }

  r = menu_function2();
  if (r != 0) {
    if (r == 1) counter_adjust();
    else if (r == 2) speed_adjust();
    else if (r == 3) braking_adjust();
    else if (r == 4) other_adjust();
    else if (r == 5) {
      display.clearDisplay();
      text("ACTIVATED!", 8, 24);
      display.display();
      remote_control();
    }
    else if (r == 6) headlight();
    sust_cracker_nut();
    while (digitalRead(swl) == LOW || digitalRead(swr) == LOW);
  }


  //  sl = sonarl.ping_cm();
  //  sf = sonarf.ping_cm();
  //  sr = sonarr.ping_cm();
  //  check();
  //  if(sl>5 && sl<20) digitalWrite(calout, HIGH);
  //  if (sf > 7 && sf < 20) digitalWrite(red, HIGH);
  //  if(sr>5 && sr<20) digitalWrite(calout, HIGH);

  //  Serial.println(colour());


}
