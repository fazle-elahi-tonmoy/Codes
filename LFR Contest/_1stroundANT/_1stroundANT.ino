#include<NewPing.h>
int lmf = 4, lmb = 3, rmf = 6, rmb = 5;
int trf = 22, ecf = 24, trl = 26, ecl = 28, trr = 50, ecr = 52, maxdis = 18, middis = 13, sf, sr,sl;
int  k = 0, y = 0, x = 0,z=0,a, spds = 150, spdt = 100, spdl = 120, th = 500;
int v1, v2, v3, v4, v5, v6;

NewPing sonarf(trf, ecf, 200);
NewPing sonarl(trl, ecl, 200);
NewPing sonarr(trr, ecr, 200);

void setup()
{ Serial.begin(9600);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(7, OUTPUT); //7 ar 2 holo motor driver er enable pin
  pinMode(2, OUTPUT);
  //pinMode(3, OUTPUT);
  pinMode(8, INPUT);
  //digitalWrite(3, 1);
  digitalWrite(7, 1);
  digitalWrite(2, 1);
  a=digitalRead(8);
}
void sonar(){
  sf=sonarf.ping_cm();
  sl=sonarl.ping_cm();
  sr=sonarr.ping_cm();

  Serial.print(sf);
  Serial.print("\t");
  Serial.print(sl);
  Serial.print("\t");
  Serial.print(sr);
  Serial.print("\n");
  

}
void loop()
{
  sensor();
  

  if ((v1 == 1 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0) || (v1 == 1 && v2 == 1 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0)) {
    y = 1;
    st_left();
  }
  else if ((v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 1) || (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 1 && v6 == 1)) {
    y = 2;
    st_right();
  }
  else if ((v1 == 0 && v2 == 1 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0) || (v1 == 0 && v2 == 1 && v3 == 1 && v4 == 0 && v5 == 0 && v6 == 0)) {
    y = 1;
    left();
  }
  else if ((v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 1 && v6 == 0) || (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 1 && v5 == 1 && v6 == 0)) {
    y = 2;
    right();
  }
  else if (v1 == 0 && v2 == 0 && v3 == 1 && v4 == 0 && v5 == 0 && v6 == 0) l_left();
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 1 && v5 == 0 && v6 == 0) l_right();
  else if (v1 == 0 && v2 == 0 && v3 == 1 && v4 == 1 && v5 == 0 && v6 == 0) straight();

  else if (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1) {
    leftlog();
  }

  else if ((v1 == 1 && v2 == 1 && v3 == 1 && v4 == 0 && v5 == 0 && v6 == 0) || (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 0 && v6 == 0) || (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 0)) {
    y = 1;
    leftlog2();
  }

  else if ((v1 == 0 && v2 == 0 && v3 == 0 && v4 == 1 && v5 == 1 && v6 == 1) || (v1 == 0 && v2 == 0 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1) || (v1 == 0 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1)){ 
    rightlog2();
  }
  else if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0 && v5 == 0 && v6 == 0) {
    sr=sonarr.ping_cm();
    if(sr<20 && sr!=0){ 
      while(1){
        cavelog();
        if(v1!=1 ||v2!=1 ||v3!=1 ||v4!=1 ||v5!=1 ||v6!=1) break;
      }
    }
    
    else if(sr>20 && sr!=0){
    if (y == 1) st_right();
    else if (y == 2) st_left();
  }
  }

  else if (v1 == 1 &&  v6 == 1 && (v3==0||v4==0)){
    straight();
    if(a==0) a=1;
    if (a==1) a=2;  
  }
  else left();
}
