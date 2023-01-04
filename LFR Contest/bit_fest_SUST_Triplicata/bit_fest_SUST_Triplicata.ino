#include<EEPROM.h>
#include<NewPing.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);

//for sonar sensor
#define trig 4
#define ecf 7
#define ecl 8
#define ecr 3
short int sf = 0, sl = 0, sr = 0;
short int midpoint = 15, wallp = 10, error = 0;

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
short int spr = 23;
//int btd = 60;
short int mtd = 200;
#define dt 15
#define br 70
short int k = 0;
short int base = 120;
short int peak = 390;
short int cl = base;
short int d = 3;
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

//for debug light && switches
#define d30 12
#define d90 13
#define lb 2
#define rb 11
short int menu = 1;
String value;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(lb, INPUT_PULLUP);
  pinMode(rb, INPUT_PULLUP);
  pinMode(d30, OUTPUT);
  pinMode(d90, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);

  for (short int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  counter = EEPROM.read(6);

  Serial.begin(9600);

  sust_triplicata();
}

void loop() {
  short int r = getclick();
  if (r > 0) {
    if (r == 1) {
      line_follow();
      mos(0, 0);
    }
    else if (r == 2) {
      while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) analog_reading_display();
    }
    else if (r == 3) {
      while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) sonar_reading_display();
    }
    //    else if (r == 2) {
    //      while (digitalRead(lb) == HIGH && digitalRead(rb) == HIGH) digital_reading_display();
    //    }
    sust_triplicata();
  }
}
