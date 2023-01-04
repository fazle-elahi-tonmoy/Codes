#include<EEPROM.h>
#include<NewPing.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);

//for sonar sensor
#define trigf 38
#define ecof 40
#define trigl 24
#define ecol 22
#define trigr 52
#define ecor 50
short int sf = 0, sl = 0, sr = 0;
short int object_boundary = 15 , wall_boundary = 15 , midpoint = 16, wallp = 8, error = 0;
short int turn = 250;
NewPing sonarl(trigl, ecol, 90);
NewPing sonarf(trigf, ecof, 90);
NewPing sonarr(trigr, ecor, 90);

//for motor driver
#define lmf 3
#define lmb 2
#define rmf 6
#define rmb 5
short int lowest_speed = 80;

//for leds and switches
#define ub 8
#define mb 9
#define db 10
#define head_left1 26
#define head_left2 28
#define head_right1 48
#define head_right2 46
#define blue 13
#define green 12
#define red 11
short int upmenu = 1;
short int downmenu = 1;
short int head = 0;
String value;


//for line follow
short int spl = 25;
short int spr = 24;
#define dt 10
#define br 70
short int mtd = 80;
short int k = 0;
short int base = 160;
short int peak = 520;
short int cl = base;
short int d = 4;
short int brake = cl / d;
short int counter = 0;
short int tcount = 0;
byte mode = 1;

//for 30 & 90 degree and other logic
short int k30 = 0;
short int k90 = 0;
short int mov = 0;
short int cross = 0;
unsigned long mi1 = 0, mi2 = 0, m81 = 0, m82 = 0, mi3 = 0;

//for ir sensor logic
short int bin = 0;
short int sum = 0;
short int sensor[] = {0, 0, 0, 0, 0, 0};
short int bina[] = {1, 2, 4, 8, 16, 32};

//for calibration & store
short int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
short int maximum[] = {0, 0, 0, 0, 0, 0};
short int trash[] = {0, 0, 0, 0, 0, 0};
float cal_p = 0.5;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(ub, INPUT_PULLUP);
  pinMode(mb, INPUT_PULLUP);
  pinMode(db, INPUT_PULLUP);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(head_left1, OUTPUT);
  pinMode(head_left2, OUTPUT);
  pinMode(head_right1, OUTPUT);
  pinMode(head_right2, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(7, OUTPUT);


  for (short int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  counter = EEPROM.read(6);
  spl = EEPROM.read(7);
  spr = EEPROM.read(8);
  mtd = EEPROM.read(9);
  d = EEPROM.read(10);
  base = EEPROM.read(11) * d;
  peak = EEPROM.read(12) * d;
  cl = base;
  object_boundary = EEPROM.read(13);
  wall_boundary = EEPROM.read(14);
  midpoint = EEPROM.read(15);
  wallp = EEPROM.read(16);
  cal_p = EEPROM.read(17) * 0.1;
  Serial.begin(9600);
  sust_triplicata();
}

void loop() {
  int r = getclickup();
  if (r != 0) {
    if (r == 1) line_follow();
    else if (r == 2) text_callibrating();
    else if (r == 3) {
      display.clearDisplay();
      text("STARTING..", 4, 24);
      display.display();
      while (digitalRead(mb) == HIGH) mos(10 * spl, 10 * spr);
      while (digitalRead(mb) == LOW) mos(0, 0);
    }
    else if(r == 4) remote_control();
    else if (r == 5) light_control();
    sust_triplicata();
  }
  r = getclickdown();
  if (r != 0) {
    if (r == 1) while (digitalRead(mb) == HIGH) analog_reading_display() ;
    else if (r == 2) while (digitalRead(mb) == HIGH) digital_reading_display() ;
    else if (r == 3) while (digitalRead(mb) == HIGH) sonar_reading_display() ;
    else if (r == 4) speed_adjust();
    else if (r == 5) adjust();
    while (digitalRead(mb) == LOW);
    sust_triplicata();
  }
  getclickmid();
}
