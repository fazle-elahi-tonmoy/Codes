#define left_motor_forward 3
#define left_motor_backward 4
#define right_motor_forward 7
#define right_motor_backward 8
#define left_motor_speed 5
#define right_motor_speed 6
#define head_light 13
#define spl 25 //left motor speed coeficient
#define spr 25 //right motor speed coeficient
#define sw 2
#define tsp 120
#define br 70
#define tbr 60
#define stp_timer 300
#define node_delay 10
char flag = 's', cross = 's';
int pos;
//unsigned long int m1, m2;
uint32_t m1, m2;

int s[6]; //this is for storing analog value of each sensor
int thresould[] = {512, 512, 512, 512, 512, 512}; //this is the mid value for each sensor. use this array if you want to adjust midoint of each sensor individually
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(head_light, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  line_follow();
}

void loop() {
}
