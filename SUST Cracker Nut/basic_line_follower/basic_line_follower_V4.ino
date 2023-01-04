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
#define ecl 44
#define trf 38
#define ecf 40
#define trr 34
#define ecr 36
int sf = 0, sl = 0, sr = 0;
int object_boundary = 15, wall_boundary = 15, midpoint = 12, turn = 350;

NewPing sonarl(trl, ecl, 90);
NewPing sonarf(trf, ecf, 90);
NewPing sonarr(trr, ecr, 90);

// for motor driver
#define lmf 2
#define lmb 3
#define rmf 5
#define rmb 4
#define switchin 24

//for line follow
int spl = 25;
int spr = 22;
int btd = 60;
int mtd = 200;
#define dt 10
#define br 60
int k = 0;
int base = 40;
int peak = 160;
int cl = base;
int d = 2;
int brake = cl / d;
int counter = 0;
int tcount = 0;
int mode = 1;

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
#define calin 22
int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
int maximum[] = {0, 0, 0, 0, 0, 0};
int trash[] = {0, 0, 0, 0, 0, 0};
float cal_p = 0.5;

//for debug light
#define red 9
#define green 11
#define blue 13

// for motor driver

void mos(int a , int b) {
  if (a >= 0) {
    analogWrite(rmf, a);
    analogWrite(rmb, 0);
  }
  else if (a < 0) {
    a = -a;
    analogWrite(rmf, 0);
    analogWrite(rmb, a);
  }
  if (b >= 0) {
    analogWrite(lmf, b);
    analogWrite(lmb, 0);
  }
  else if (b < 0) {
    b = -b;
    analogWrite(lmf, 0);
    analogWrite(lmb, b);
  }
  return ;
}

void motorSpeedL(int speedA, int speedB) {
  mos(speedA, -speedB);
}

void motorSpeedR(int speedA, int speedB) {
  mos(-speedA, speedB);
}
void motorSpeedB(int speedA, int speedB) {
  mos(-speedA, -speedB);
}

void motorSpeedS() {
  mos(0, 0);
}




void cal() {
  motorSpeedR(250, 250);
  for (int c = 0; c < 3000 ; c++)
    for (int i = 0; i < 6; i++) {
      sensor[i] = analogRead(i);
      maximum[i] = max(maximum[i], sensor[i]);
      minimum[i] = min(minimum[i], sensor[i]);
    }
    motorSpeedS();
  for (int i = 0; i < 6; i++) trash[i] = ( maximum[i] + minimum[i]) * cal_p;
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i, trash[i] / 5 );
    delay(10);
  }
  return;
}






void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(calin, INPUT_PULLUP);
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
  pinMode(switchin , INPUT_PULLUP);
  digitalWrite(13, LOW);
  mos(0,0);

  for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;

  spl = EEPROM.read(6);
  spr = EEPROM.read(7);
  hpos = EEPROM.read(8);
  gpos = EEPROM.read(9);
  counter = EEPROM.read(10);
  btd = EEPROM.read(11);
  mtd = EEPROM.read(12);
  d = EEPROM.read(13);
  base = EEPROM.read(14) * d;
  peak = EEPROM.read(15) * d;
  cl = base;
  brake = cl / d;
  object_boundary = EEPROM.read(16);
  wall_boundary = EEPROM.read(17);
  midpoint = EEPROM.read(18);
  cal_p = EEPROM.read(19) * 0.1;

  //  handle.attach(8);                         //this is for when grabber was attached to bot
  //  grab.attach(9);
  //  grab.write(140);
  //  handle.write(0);
  //  delay(1500);
  //  grab.write(gpos);
  //  delay(500);
  //  handle.write(hpos);
  sust_cracker_nut();

  Serial.begin(38400);
}


// for ir sensor function

void check()
{
  sum = 0;
  bin = 0;
  //for black line(1)-- white surface(0)
  for (int i = 0; i < 6; i++) {
    sensor[i] = analogRead(i);
    if (mode == 1) (sensor[i] > trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    else if (mode == 0) (sensor[i] < trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    sum += sensor[i];
    bin += sensor[i] * bina[i];
  }
  return;
}

void sonar() {
  sl = sonarl.ping_cm();
  sf = sonarf.ping_cm();
  sr = sonarr.ping_cm();
}

void debug() {
  for (int i = 5; i >= 0 ; i--) {
    Serial.print(sensor[i]);
  }
  Serial.print("  ");
  Serial.print(mov);
  Serial.print("  ");
  Serial.print(sl);
  Serial.print("  ");
  Serial.print(sf);
  Serial.print("  ");
  Serial.println(sr);
}




void loop()
{
  int r = 0;
  r = menu_function1();
  if (r != 0) {
    if (r == 1) {
      delay(200);
      line_follow();
      motorSpeedS();
    }
    else if (r == 2) {
      text_callibrating();
      for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
    }
    else if (r == 3) {
      while (digitalRead(calin) == HIGH) analog_reading_display();
    }
    else if (r == 4) {
      while (digitalRead(calin) == HIGH) digital_reading_display();
    }
    else if (r == 5) {
      while (digitalRead(calin) == HIGH) sonar_reading_display();
    }
    else if (r == 6) {
      display.clearDisplay();
      text("STARTING..", 04, 24);
      display.display();
      delay(1000);
      while (digitalRead(calin) == HIGH) mos(10 * spr, 10 * spl);
      mos(0, 0);
    }
    sust_cracker_nut();
    while (digitalRead(calin) == LOW || digitalRead(switchin) == LOW);
  }

  r = menu_function2();
  if (r != 0) {
    if (r == 1) counter_adjust();
    else if (r == 2) speed_adjust();
    else if (r == 3) braking_adjust();
    else if (r == 4) {
      display.clearDisplay();
      text("ACTIVATED!", 8, 24);
      display.display();
      remote_control();
    }
    sust_cracker_nut();
    while (digitalRead(calin) == LOW || digitalRead(switchin) == LOW);
  }


  //  sl = sonarl.ping_cm();
//    sf = sonarf.ping_cm();
  //  sr = sonarr.ping_cm();
  //  check();
  //  if(sl>5 && sl<20) digitalWrite(calout, HIGH);
//    if(sf>7 && sf<20) digitalWrite(red, HIGH);
  //  if(sr>5 && sr<20) digitalWrite(calout, HIGH);

}
