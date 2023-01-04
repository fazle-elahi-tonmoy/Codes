#include <SoftwareSerial.h>
#include<NewPing.h>
NewPing sonar(16, 16, 50);
SoftwareSerial bt(13, 12);
#define spd 25
int spdl, spdr;
#define left_motor_forward 7
#define left_motor_backward 8
#define stby 6
#define right_motor_forward 4
#define right_motor_backward 5
#define left_motor_speed 9
#define right_motor_speed 3
#define front_light 15
#define back_light 14
#define sw 2
bool mode = 0;
int s = 10;
char x;
long int m1, m2;

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH);
  pinMode(front_light, OUTPUT);
  pinMode(back_light, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, 1);
  pinMode(sw, INPUT_PULLUP);
  m1 = millis();
  motor(0, 0);
  Serial.begin(38400);
  bt.begin(9600);
}

void loop() { // run over and over
  button();
  speed_control();
  obstacle();
  if (bt.available()) {
    x = bt.read();
    command();
  }
}
