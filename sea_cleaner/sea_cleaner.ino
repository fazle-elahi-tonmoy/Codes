#include<Servo.h>
#define mf 2
#define mb 4
#define me 6
#define relayf 7
#define relayb 5

int front = 120, left = 170, right = 65;
int th = 155;
char data;

Servo guide;

void setup() {
  pinMode(relayf, OUTPUT);
  pinMode(relayb, OUTPUT);
  pinMode(mf, OUTPUT);
  pinMode(mb, OUTPUT);
  pinMode(me, OUTPUT);
  guide.attach(9);
  guide.write(front);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    data =  Serial.read();
    Serial.print(data);
    Serial.print("\n");
    if (data == 'F')      forward();
    else if (data == 'B') backward();
    else if (data == 'L') guide.write(left);
    else if (data == 'R') guide.write(right);
    else if (data == 'G') forward_left();
    else if (data == 'I') forward_right();
    else if (data == 'H') backward_left();
    else if (data == 'J') backward_right();
    else if (data == 'S') stop_bot();
    else if (data == '0') th = 0;
    else if (data == '1') th = 60;
    else if (data == '2') th = 80;
    else if (data == '3') th = 100;
    else if (data == '4') th = 120;
    else if (data == '5') th = 140;
    else if (data == '6') th = 160;
    else if (data == '7') th = 180;
    else if (data == '8') th = 200;
    else if (data == '9') th = 225;
    else if (data == 'q') th = 255;
    else if (data == 'W') ref();
    else if (data == 'U') reb();
    else if (data == 'w' || data == 'u') relaystp();
    else stop_bot();

  }
}

void forward() {
  analogWrite(me, th);
  digitalWrite(mf, HIGH);
  digitalWrite(mb, LOW);
  guide.write(front);
}

void forward_left() {
  analogWrite(me, th);
  digitalWrite(mf, HIGH);
  digitalWrite(mb, LOW);
  guide.write(left);
}

void forward_right() {
  analogWrite(me, th);
  digitalWrite(mf, HIGH);
  digitalWrite(mb, LOW);
  guide.write(right);
}

void backward() {
  analogWrite(me, th);
  digitalWrite(mf, LOW);
  digitalWrite(mb, HIGH);
  guide.write(front);
}

void backward_left() {
  analogWrite(me, th);
  digitalWrite(mf, LOW);
  digitalWrite(mb, HIGH);
  guide.write(left);
}

void backward_right() {
  analogWrite(me, th);
  digitalWrite(mf, LOW);
  digitalWrite(mb, HIGH);
  guide.write(right);
}

void stop_bot(){
  analogWrite(me, th);
  digitalWrite(mf, 0);
  digitalWrite(mb, 0);
  guide.write(front);  
}

void ref(){
  digitalWrite(relayf, HIGH);
  digitalWrite(relayb, LOW);
}

void reb(){
  digitalWrite(relayb, HIGH);
  digitalWrite(relayf, LOW);
}

void relaystp(){
  digitalWrite(relayf, LOW);
  digitalWrite(relayb, LOW);
}



