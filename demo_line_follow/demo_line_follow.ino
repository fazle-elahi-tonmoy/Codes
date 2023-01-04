#define left_motor_forward 3
#define left_motor_backward 4
#define right_motor_forward 7
#define right_motor_backward 8
#define left_motor_speed 5
#define right_motor_speed 6
#define push_button 2
#define blue_led 13

int s[6]; //this is for storing analog value of each sensor
int thresould = 512; //this is the mid value
int base[6]={1,2,4,8,16,32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
char flag = 's'; //this variable will indicate if you will have to sharp turn or not

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(blue_led, OUTPUT); //this is to indicate if robot got any turn signal
  pinMode(push_button, INPUT_PULLUP); //i will describe about this later
}

void loop() {
  reading();
  show_the_value(); //this is to check the sensor reading in serial monitor. comment this out if you make the robot line follow because this code slows the robot

  //line follow starts here. comment this out if you want to check only sensor reading but not to follow the line.
  line_follow();
  
}
