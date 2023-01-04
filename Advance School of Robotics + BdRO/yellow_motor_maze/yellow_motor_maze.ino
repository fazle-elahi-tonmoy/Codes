#include<EEPROM.h>

#define left_motor_forward 6
#define left_motor_backward 5
#define right_motor_forward 9
#define right_motor_backward 10
#define head_light1 13
#define head_light2 4
#define sw 12


#define spl 12 //left motor speed coeficient
#define spr 10 //right motor speed coeficient
#define wait 40 //waiting time before turning
#define tsp 100 //speed of motor while turning
#define tbr 40  //how long it will go reverse to normalise angular momentum
#define side 2 //1 means left hand rule, 2 means rught hand rule
#define node_delay 20 // for how long it will go forward to verify a node
#define stop_timer 100 // how long it will go forward to verify sgop point
#define u_turn_timer 150 //how long it will go forward before turning back
#define rotate 800

int maximum[6], minimum[6], mid[6];
char flag = 's';

int s[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor
unsigned long m1, m2, m3;
byte scan[50];
byte counter = 0;
byte cross = 0;

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(head_light1, OUTPUT);
  pinMode(head_light2, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 5;
    maximum[i] = EEPROM.read(i + 6) * 5;
    minimum[i] = EEPROM.read(i + 12) * 5;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
}

void loop() {
  int r = push();
  if (r == 1) line_follow();
  else if (r == 2) maze_scan(0);
  else if (r == 3) maze_scan(1);
  else if (r == 4) maze_solve(0);
  else if (r == 5) cal();
  else if (r == 6) motor(10 * spl, 10 * spr);
  else if (r == 7) while (1) show_the_value();// to test the value of sensor in serial monitor
  else if (r == 8) for (int i = 0; i <= EEPROM.read(19); i++) Serial.println(EEPROM.read(i+20));
  else if (r==9) bluetooth();
  else if (r==10) {
    motor(100,-100); delay(rotate);
    motor(-100, 100); delay(tbr); motor(0,0);
  }
}
