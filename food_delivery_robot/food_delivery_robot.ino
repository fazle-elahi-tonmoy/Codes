#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>
SoftwareSerial mySerial(11, 12);
NewPing sonar(2, 4, 20);
Servo servo;

int s[6], sensor, sum, ss[2];
int threshold = 900;
float avg, error;
float kp = 60, PID;
bool table[4] = { 0, 0, 0, 0 };
int count = 0;
bool order = 0;
uint32_t order_timer, sonar_timer, obs_timer;
int distance;
int baseL = 120, baseR = 120;
char flag = 's';


int lms = 6, rms = 5, lmf = 9, lmb = 10, rmf = 7, rmb = 8;


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  servo.attach(3);
  servo.write(90);
}

void loop() {
  Serial_Test();

  if (mySerial.available()) {
    char x = mySerial.read();
    Serial.print(x);
    if (x >= '1' && x <= '4') table[x - '1'] = 1;
    order = 1;
    order_timer = millis();
  }

  if (order && millis() - order_timer > 1000) lfr();
}
