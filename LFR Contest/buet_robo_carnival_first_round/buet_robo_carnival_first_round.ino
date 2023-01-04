#include<EEPROM.h>
#include<NewPing.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

//for sonar sensor
#define trf 32
#define ecf 34
#define trr 28
#define ecr 30
#define trl 24
#define ecl 26
int sf = 0, sl = 0, sr = 0, obs = 0, s[50];

NewPing sonarl(trl, ecl, 90);
NewPing sonarf(trf, ecf, 90);
NewPing sonarr(trr, ecr, 90);

// for motor driver
#define pwma 2
#define pwmb 7
#define n1 4
#define n2 3
#define n3 6
#define n4 5
#define switchin 51
#define switchout 53

//for line follow
int spl = 25;
int spr = 22;
#define dt 10
#define br 40
#define btd 80
#define mtd 200
int k = 0;
int base = 80;
int peak = 160;
int cl = base;
int d = 2;
int brake = cl / d;
int counter = 0;
int ccount = 0;
int scount = 0;
int ecount = 0;
int side[2];

//for 30degeree & 90 degree && other logic
int k30 = 0;
int k90 = 0;
int mov = 0;
int cross = 0;
unsigned long mi1 = 0, mi2 = 0, mi3 = 0, m81 = 0, m82 = 0 ;


//for ir sensor logic
int bin = 0;
int sum = 0;
int sensor[] = { 0, 0, 0, 0, 0, 0};
int bina[] = {1, 2, 4, 8, 16, 32 };
int p = 0;

//for calibration & store
#define calout 23
#define calin 25
int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
int maximum[] = {0, 0, 0, 0, 0, 0};
int trash[] = {0, 0, 0, 0, 0, 0};

//for debug light
#define d30 47
#define d90 43

// for motor driver

void mos(int a , int b) {
  if (a >= 0) {

    digitalWrite(n1, HIGH);
    digitalWrite(n2, LOW);
  }
  else if (a < 0) {
    a = -a;
    digitalWrite(n1, LOW);
    digitalWrite(n2, HIGH);
  }
  if (b >= 0) {

    digitalWrite(n3, HIGH);
    digitalWrite(n4, LOW);
  }
  else if (b < 0) {
    b = -b;
    digitalWrite(n3, LOW);
    digitalWrite(n4, HIGH);
  }
  analogWrite(pwma, a);
  analogWrite(pwmb, b);
  return ;

}
void motorSpeed(int speedA, int speedB) {
  digitalWrite(n1, HIGH);
  digitalWrite(n3, HIGH);
  digitalWrite(n2, LOW);
  digitalWrite(n4, LOW);
  analogWrite(pwma, speedA);
  analogWrite(pwmb, speedB);
  return ;
}

void motorSpeedL(int speedA, int speedB) {
  if (speedA >= 100 && speedB >= 100) {
    analogWrite(pwma, speedA);
    analogWrite(pwmb, speedB);
  }
  else {
    analogWrite(pwma, 150);
    analogWrite(pwmb, 150);
  }
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
  return ;
}

void motorSpeedR(int speedA, int speedB) {
  if (speedA >= 100 && speedB >= 100) {
    analogWrite(pwma, speedA);
    analogWrite(pwmb, speedB);
  }
  else {
    analogWrite(pwma, 150);
    analogWrite(pwmb, 150);
  }
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
  return ;
}
void motorSpeedB(int speedA, int speedB) {
  digitalWrite(n1, LOW);
  digitalWrite(n3, LOW);
  digitalWrite(n2, HIGH);
  digitalWrite(n4, HIGH);
  analogWrite(pwma, speedA);
  analogWrite(pwmb, speedB);
}

void motorSpeedS() {

  digitalWrite(n2, LOW);
  digitalWrite(n3, LOW);
  digitalWrite(n1, LOW);
  digitalWrite(n4, LOW);
  analogWrite(pwma, 0);
  analogWrite(pwmb, 0);
  return ;
}




void cal() {
  digitalWrite(calout, HIGH);
  //  text_callibrating();
  motorSpeedR(250, 250);
  int c = 0;
  while (c < 10000) {
    for (int i = 0; i < 6; i++) {
      sensor[i] = analogRead(i + 10);
      maximum[i] = max(maximum[i], sensor[i]);
      minimum[i] = min(minimum[i], sensor[i]);
    }

    c++;
  }
  motorSpeed(0, 0);
  delay(500);
  for (int i = 0; i < 6; i++) trash[i] = ( maximum[i] + minimum[i]) / 2;
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i, trash[i] / 5 );
    delay(10);
  }
  digitalWrite(calout, LOW);
  return;
}






void setup()
{
  TCCR3B = 3;
  TCCR4B = 3;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  sust_cracker_nut();
  pinMode(calin, INPUT);
  pinMode(calout, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(d30 , OUTPUT);
  pinMode(d90 , OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(switchout , OUTPUT);
  pinMode(switchin , INPUT);
  digitalWrite(switchout, HIGH);
  digitalWrite(13, LOW);

  for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  counter = EEPROM.read(10);
  side[0] = EEPROM.read(11);
  side[1] = EEPROM.read(12);
  Serial.begin(9600);
}


// for ir sensor function

void check()
{
  sum = 0;
  bin = 0;
  //for black line(1)-- white surface(0)
  for (int i = 0; i < 6; i++) {
    sensor[i] = analogRead(i + 10);
    (sensor[i] > trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    sum += sensor[i];
    bin += sensor[i] * bina[i];
  }

  //  debug();

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
  int r = getclick1();
  if (r != 0) {
    int p = map(analogRead(8), 740, 1023, 0, 100);
    if (p <= 40) {
      while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) text_battery_low();
      display.clearDisplay();
      display.display();
      delay(1000);
    }
    if (r == 1) {
      text_line_follow();
      line_follow();
    }
    else if (r == 2) {
      while (digitalRead(calin) == LOW) analog_reading_display();
    }
    else if (r == 3) {
      while (digitalRead(calin) == LOW) digital_reading_display();
    }
    else if (r == 4) {
      while (digitalRead(calin) == LOW) sonar_reading_display();
    }
    else if (r == 5) {
      text_callibrating();
      for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
    }
    if (r <= 5) {
      display.clearDisplay();
      display.display();
      delay(500);
    }
    sust_cracker_nut();
  }

  r = getclick2();
  if (r != 0) {
    if (r == 1) {
      EEPROM.write(10, 0);
      delay(10);
      counter = EEPROM.read(10);
    }
    else if (r == 2) {
      EEPROM.write(10, 1);
      delay(10);
      counter = EEPROM.read(10);
    }
    else if (r == 3) {
      EEPROM.write(10, 2);
      delay(10);
      counter = EEPROM.read(10);
    }
    else if (r == 4) {
      EEPROM.write(10, 4);
      EEPROM.write(9, 1);
      delay(10);
      counter = EEPROM.read(10);
      ccount = EEPROM.read(9);
    }
    else if (r == 5) {
      mos(10 * spr, 10 * spl);
      while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW);
      motorSpeedS();
    }
    else if (r == 6) {
      while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) text_battery_check();
    }
    if (r <= 6) {
      display.clearDisplay();
      display.display();
      delay(500);
    }
    int p = map(analogRead(8), 740, 1023, 0, 100);
    if (p <= 40) {
      while (digitalRead(calin) == LOW && digitalRead(switchin) == LOW) text_battery_low();
      display.clearDisplay();
      display.display();
      delay(500);
    }
    sust_cracker_nut();
    delay(500);
  }
  //      sl = sonarl.ping_cm();
  //    sf = sonarf.ping_cm();
  //    sr = sonarr.ping_cm();
  //    check();
  //      if(sl>5 && sl<20) digitalWrite(calout, HIGH);
  //    if(sf>2 && sf<20) digitalWrite(calout, HIGH);
  //    if(sr>5 && sr<20) digitalWrite(calout, HIGH);
}





