 #include<EEPROM.h>
#include<NewPing.h>
//#define inc 9
// for motor driver
#define pwma 11
#define pwmb 7
#define n1 12
#define n2 13
#define n3 9
#define n4  10

#define trf 32
#define ecf 33
#define trl 30
#define ecl 31
#define trr 34
#define ecr 35
#define lf_mz 6 //line_follow
#define ms_mr 5 //maze solving
int sl,sr;

NewPing sonarl(trl, ecl, 300);
NewPing sonarr(trr, ecr, 300);

//for line follow 
#define sp 25    // speed 
#define dt 10    //delay
int k = 0;       //??????????????????????????

//for 30degeree & 90 degree && other logic 
int k30 = 0;
int k90 = 0;
int mov=0;
int cross=0;
int robot=0;
int prob[255], aa=0, bb=0, cc=0, ii=0;
unsigned long mi1=0, mi2=0,m81=0,m82=0 ;


//for ir sensor logic 
int bin = 0;
int sum = 0;
int sensor[] = { 0, 0, 0, 0, 0, 0};
int bina[]= {1, 2, 4, 8, 16, 32 };
int p=0;

//for calibration & store 
#define calout  53
#define calin 22
int minimum[] = {1024, 1024, 1024, 1024, 1024, 1024};
int maximum[] = {0, 0, 0, 0, 0, 0};
int trash[] = {0, 0, 0, 0, 0, 0};

//for debug
#define d90 50
#define light 53


void sonar(){
  sl=sonarl.ping_cm();
  sr=sonarr.ping_cm();

  Serial.print(sl);
  Serial.print("\t");
  Serial.print(sr);
  Serial.print("\t");
  Serial.print("\n");
  

}

// for motor driver 

void mos(double a , double b) {
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
      sensor[i] = analogRead(i+8);               // (i+8) ata ki amra a8 use korasi tar jonno?? na onno kono karaon e??
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
  return;       // return na dile ki problem hote pare????
}






void setup() {
  //pinMode(inc, INPUT);    // inc er kaj ta ki actually???
  pinMode(calin, INPUT);
  pinMode(calout, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
 pinMode(light , OUTPUT);    //??????????????
 pinMode(d90 , OUTPUT);      //?????????????
 pinMode(lf_mz, INPUT);
 pinMode(ms_mr, INPUT);
 
 

  if (digitalRead(calin) == HIGH) cal();
  else if(lf_mz == 0) robot=0;
  else if(lf_mz ==1 ){
    if(ms_mr == 0) robot=1;
    else if(ms_mr ==1) robot=2;
  }
  
  

  for (int i = 0; i < 6; i++) trash[i] = EEPROM.read(i) * 5;
  Serial.begin(9600);
}


// for ir sensor function

void check()
{
    sum=0;
    bin=0;
//for black line(1)-- white surface(0)
  for (int i = 0; i < 6; i++) {
    sensor[i] = analogRead(i+8);
    (sensor[i]>trash[i])?sensor[i]=1 : sensor[i]=0 ;
  //  if (sensor[i] > trash[i])sensor[i] = 1;
  //  else sensor[i] = 0;
    sum+=sensor[i];
    bin+=sensor[i]*bina[i]; 
  } 
  //bin = sensor[0] * 1 + sensor[1] * 2 + sensor[2] * 4 + sensor[3] * 8 + sensor[4] * 16 + sensor[5] * 32 + sensor[6] * 64 + sensor[7] * 128;
   for (int i = 0; i < 6; i++) {
    //Serial.print(sensor[i]);
   }
//   Serial.print("\t");
//    Serial.print(sr);
//    Serial.print("\t");
//    Serial.print(" ");
//    Serial.print(sum);
//    Serial.print("   ");
//    Serial.println(bin);
  return;
}

void loop(){
  if(robot==0) line_follow();
  else if(robot==1) maze_scanner();
  else if(robot==2) maze_runner();
}
 


