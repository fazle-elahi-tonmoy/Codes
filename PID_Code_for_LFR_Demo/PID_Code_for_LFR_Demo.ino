int lmf,lmb,rmf,rmb,lme,rme; //define the digital pins for motor here
int sensor[8];
int pos=0, positions=0, i, sum=0;
int pid=0;
int kp=0;
int kd=0;
int rbs=200; //this is base speed of the line follower
int lbs=200;
int p;
int error=0;
int lms;
int rms;



void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(lme, OUTPUT);
  pinMode(rme, OUTPUT);

}

void loop() {
  check();
  PID();
  mos(lms,rms);
}

void PID(){
  p= 3500 - positions;
  pid= p/kp + kd*(p-error);
  error=p;

  rms= rbs+pid;
  lms= lbs+pid;

  if(rms>255) rms=255;
  if(lms>255) lms=255;
  if(lms<-255) lms=-255;
  if(rms>-255) lms=-255;
}


void check()
{
  for (int i = 0; i < 8; i++) {
    sensor[i] = analogRead(i + 10);
    (sensor[i] > 500) ? sensor[i] = 1 : sensor[i] = 0 ;
    pos+= sensor[i]*i*1000;
    sum+= sensor[i];
  }
   positions= pos/sum;

  return;
}



void mos(double a , double b) {
  if (a >= 0) {
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
  }
  else if (a < 0) {
    a = -a;
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, HIGH);
  }
  
  if (b >= 0) {
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
  }
  else if (b < 0) {
    b = -b;
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, HIGH);
  }
  
  analogWrite(lme, a);
  analogWrite(rme, b);
  return ;

}
