#include<EEPROM.h>
#include<NewPing.h>

//for sonar sensor
#define trig 4
#define ecf 7
#define ecl 8
#define ecr 3
short int sf = 0, sl = 0, sr = 0;
short int midpoint = 13, wallp = 5, error = 0, boundary = 15, turn = 250;

NewPing sonarl(trig, ecl, 90);
NewPing sonarf(trig, ecf, 90);
NewPing sonarr(trig, ecr, 90);

//for motor driver
#define lmf 10
#define lmb 5
#define rmf 9
#define rmb 6
short int lowest_speed = 80;

//for line follow
short int spl = 25;
short int spr = 24;
//int btd = 60;
short int mtd = 200;
#define dt 15
#define br 60
short int k = 0;
short int base = 160;
short int peak = 480;
short int cl = base;
short int d = 4;
short int brake = cl / d;
short int counter = 0;
byte mode = 1;

//for 30 & 90 degree and other logic
short int k30 = 0;
short int k90 = 0;
short int mov = 0;
short int cross = 0;
unsigned long mi1 = 0, mi2 = 0, mi3 = 0, m81 = 0, m82 = 0;

//for ir sensor logic
short int bin = 0;
short int sum = 0;
short int sensor[] = {0, 0, 0, 0, 0, 0};
short int bina[] = {1, 2, 4, 8, 16, 32};

//for calibration & store
short int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
short int maximum[] = {0, 0, 0, 0, 0, 0};
short int trash[] = {0, 0, 0, 0, 0, 0};

//for debug light && switches
#define d30 12
#define d90 13
#define lb 2
#define rb 11


void setup() {
  pinMode(lb, INPUT_PULLUP);
  pinMode(rb, INPUT_PULLUP);
  pinMode(d30, OUTPUT);
  pinMode(d90, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(18, 0);


  for (short int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  counter = EEPROM.read(6);

  Serial.begin(9600);
}

void loop() {
  leftswitch();
  short int r = rightswitch();
  if (r > 0) {
    if (r == 1) {
      line_follow();
      mos(0, 0);
    }
    else if (r == 2) cal();
  }
  check();
  sonar();
  debug();
}
