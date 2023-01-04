#include<EEPROM.h>
#include<NewPing.h>
#include<Servo.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

Servo lfang;
Servo rfang;

//for sonar sensor
#define trigf 38
#define ecof 40
#define trigl 24
#define ecol 22
#define trigr 52
#define ecor 50
short int midpoint = 16, wallp = 8, error = 0;
byte sf, sl, sr, object_boundary = 15 , wall_boundary = 15, o_direction;
NewPing sonarl(trigl, ecol, 90);
NewPing sonarf(trigf, ecof, 90);
NewPing sonarr(trigr, ecor, 90);

//for motor driver
byte lmf, lmb, rmf, rmb, lvalue = 32, rvalue = 65;

//for servos
byte intl = 150, intr = 30, fl = 80, fr = 100, fang = 0;


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
#define buzzer 30
byte upmenu = 1, downmenu = 1, head = 0, state = 11;
String value;


//for line follow....................................................................
#define dt 10
short int sp = 25, spe = 0, line_d = 0;
byte tsp = 200, br = 70, ltd = 10, mtd = 80, rtd = 100, stp_delay = 50;
short int k = 0, d = 4, counter = 0;
unsigned int base = 160, peak = 520, cl, brake, o1, o2, rotation;
byte side = 0, tcount = 0, mode = 1, trigger = 1, turn = 0, direct = 111;

//for 30 & 90 degree and other logic
byte k30 = 0, k90 = 0, mov = 0, cross = 0;
unsigned long mi1 = 0, mi2 = 0, m81 = 0, m82 = 0, mi3 = 0, mi4 = 0;

//for ir sensor logic
byte bin = 0, sum = 0, bina[] = {1, 2, 4, 8, 16, 32};
short int sensor[6];

//for calibration & store
short int minimum[6] = {1023, 1023, 1023, 1023, 1023, 1023};
short int maximum[6] = {0, 0, 0, 0, 0, 0};
short int trash[6] = {500, 500, 500, 500, 500, 500};
float cal_p = 0.5, line_p;

//for maze solving
byte scan[255], m_base = 50;

//for snake game
short int pos[400] = {600, 400, 200, 000};
short int foodx, foody, dir = 3, len = 4, dl = 100;
bool eat = 1, s_b = 0;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  //  display.setTextColor(BLACK, WHITE);
  display.invertDisplay(false);

  pinMode(ub, INPUT_PULLUP);
  pinMode(mb, INPUT_PULLUP);
  pinMode(db, INPUT_PULLUP);
  pinMode(head_left1, OUTPUT);
  pinMode(head_left2, OUTPUT);
  pinMode(head_right1, OUTPUT);
  pinMode(head_right2, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);

  for (byte i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  counter = EEPROM.read(6);
  sp = EEPROM.read(7);
  spe = EEPROM.read(8) - 128;
  direct = EEPROM.read(9);
  side = direct / 100;
  o_direction = (direct % 100) / 10;
  trigger = direct % 10;
  state = EEPROM.read(10);
  fang = state / 10; head = state % 10;

  d = EEPROM.read(11);
  base = EEPROM.read(12) * d * 10;
  peak = EEPROM.read(13) * d * 10;
  tsp = EEPROM.read(14) * 10;
  br = EEPROM.read(15);
  ltd = EEPROM.read(16);
  mtd = EEPROM.read(17) * 10;
  rotation = EEPROM.read(18) * 10;
  rtd = EEPROM.read(19) * 10;
  stp_delay = EEPROM.read(20) * 10;
  o1 = EEPROM.read(21) * 10;
  o2 = EEPROM.read(22) * 10;
  cl = base;
  object_boundary = EEPROM.read(25);
  wall_boundary = EEPROM.read(26);
  midpoint = EEPROM.read(27);
  wallp = EEPROM.read(28);
  cal_p = EEPROM.read(29) * 0.1;
  line_p = EEPROM.read(30) * 0.1;
  line_d = EEPROM.read(31);
  lvalue = EEPROM.read(36);
  rvalue = EEPROM.read(37);
  lmf = lvalue / 10; lmb = lvalue % 10; rmf = rvalue / 10; rmb = rvalue % 10;
  Serial.begin(38400);

  lfang.attach(4);
  rfang.attach(7);
  (fang == 0) ? lfang.write(intl) : lfang.write(fl);
  (fang == 0) ? rfang.write(intr) : rfang.write(fr);
  head_light(head);
  pinik();

}

void loop() {
  byte r = getclickup();
  if (r != 0) {
    if (r == 1) {
      byte c = 0;
      while (digitalRead(mb) == HIGH) {
        display.clearDisplay();
        (c == 0) ? text("FREE STYLE", 04, 24) : text("FIXED RUN", 10, 26);
        display.display();
        if (digitalRead(ub) == LOW) c = 1;
        else if (digitalRead(db) == LOW) c = 0;
      }
      if (long_press(0) == 0) (c == 0) ? line_follow(0, 0) : line_solve(0, 0);
    }
    else if (r == 2) maze_func();
    else if (r == 3) counter_display(0, 1);
    else if (r == 4) {
      display.clearDisplay();
      text("STARTING..", 4, 24);
      display.display();
      delay(500);
      while (digitalRead(mb) == HIGH) mos(10 * sp, 10 * sp);
      while (digitalRead(mb) == LOW) mos(0, 0);
    }
    else if (r == 5) side_selection(0);
    pinik();
  }
  r = getclickdown();
  if (r != 0) {
    if (r == 1) sensor_display();
    else if (r == 2) speed_adjust();
    else if (r == 3) braking();
    else if (r == 4) other();
    else if (r == 5) control_system();
    while (digitalRead(mb) == LOW);
    pinik();
  }
  getclickmid();
  if (Serial.available() > 0) {
    remote_control();
    pinik();
  }
}
