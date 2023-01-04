#include<EEPROM.h>
#include<NewPing.h>

// for motor driver
#define pwma 2
#define pwmb 7
#define n1 4
#define n2 3
#define n3 6
#define n4 5

//for sonar sensor
#define trf 32
#define ecf 34
#define trr 28
#define ecr 30
#define trl 24
#define ecl 26
int sf = 0, sr = 0, sl = 0, obs = 0;

NewPing sonarl(trl, ecl, 200);
NewPing sonarr(trr, ecr, 200);
NewPing sonarf(trf, ecf, 200);

//for line follow
int spl = 24;
int spr = 25;
#define dt 7
int k = 0;
byte counter=0;

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
#define calout  23
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
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
  analogWrite(pwma, speedA);
  analogWrite(pwmb, speedB);
  return ;
}
void motorSpeedR(int speedA, int speedB) {
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
  analogWrite(pwma, speedA);
  analogWrite(pwmb, speedB);
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
  delay(2000);
  motorSpeedR(200, 200);
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
{ //pinMode(inc, INPUT);
  pinMode(calin, INPUT);
  pinMode(calout, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(d30 , OUTPUT);
  pinMode(d90 , OUTPUT);

  if (digitalRead(calin) == HIGH) cal();


  for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
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
  return;
}

void sonar() {
  sf = sonarf.ping_cm();
  sr = sonarr.ping_cm();
  sl = sonarl.ping_cm();
}


void debug() {
  for (int i = 5; i >= 0 ; i--) {
    Serial.print(sensor[i]);
  }
  Serial.print("  ");
  Serial.print(mov);
  Serial.print("  ");
  Serial.print(sl);
  Serial.print(" ");
  Serial.print(sf);
  Serial.print(" ");
  Serial.println(sr);
}




void loop()
{

  check();
//  sonar();
//  debug();


  if (sf <= 30 && sf != 0 && counter ==1) {
    if (obs == 0) {
      motorSpeedB(150, 150);
      delay(100);
      obs = 1;
    }
    spr = 14;
    spl = 15;
    digitalWrite(calout, HIGH);
    mi3 = millis ();
  }


