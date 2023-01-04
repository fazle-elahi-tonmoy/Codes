#include<Servo.h>
#define lmf 4
#define lmb 2
#define lms 3
#define rmf 7
#define rmb 8
#define rms 11
#define grab 40
#define drop 110
#define rise 180
#define lower 50
Servo hand;
Servo lift;
void setup() {
  Serial.begin(9600);
  hand.attach(5);
  lift.attach(6);
  hand.write(drop);
  lift.write(rise);
  pinMode(lmf , OUTPUT);
  pinMode(lmb , OUTPUT);
  pinMode(rmf , OUTPUT);
  pinMode(rmb , OUTPUT);
  remote_control();
}

void loop() {
}
