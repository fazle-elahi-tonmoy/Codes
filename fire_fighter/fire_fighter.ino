#include<NewPing.h>
NewPing sonar(11, 12, 100);

int inab = 4, inbb = 2, incb = 8, indb = 7, inaf = 13, inbf = 16, incf = 14, indf = 15;
int relay = 10;
char data;
int th = 250;
int limit=50;
int mode = 0, sf = 0;
int maximum[] = {0, 0, 0, 0, 0};
int trash[] = {0, 0, 0, 0, 0};
int bin = 0;
int sum = 0;
int sensor[] = { 0, 0, 0, 0, 0};
int bina[] = {1, 2, 4, 8, 16};

void setup() {
  Serial.begin(9600);
  pinMode(inaf, OUTPUT);
  pinMode(inbf, OUTPUT);
  pinMode(incf, OUTPUT);
  pinMode(indf, OUTPUT);
  pinMode(inab, OUTPUT);
  pinMode(inbb, OUTPUT);
  pinMode(incb, OUTPUT);
  pinMode(indb, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
//  delay(2000);
  cal();
}


void loop() {
  if (mode == 0) manual();
  else if (mode == 1) automatic();
}

void check()
{
  bin = 0;
  for (int i = 0; i < 5; i++) {
    sensor[i] = analogRead(i + 3);
    (sensor[i] > trash[i]) ? sensor[i] = 1 : sensor[i] = 0 ;
    bin += sensor[i] * bina[i];
  }
  return;
}

void debug() {
  for (int i = 0; i < 5; i++) {
    Serial.print(sensor[i]);
    Serial.print(" ");
  }
  sf = sonar.ping_cm();
  Serial.println(sf);
}

void cal() {
  //left();
  int c = 0;
  while (c < 1000) {
    for (int i = 0; i < 5; i++) {
      sensor[i] = analogRead(i + 3);
      maximum[i] = max(maximum[i], sensor[i]);
    }
    c++;
  }
  stop_bot();
  for (int i = 0; i < 5; i++) trash[i] = (maximum[i] + limit);
  return;
}

void forward() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 1);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 1);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 1);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 1);
  digitalWrite(indf, 0);
}

void backward() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 1);
  digitalWrite(incb, 0);
  digitalWrite(indb, 1);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 1);
  digitalWrite(incf, 0);
  digitalWrite(indf, 1);
}

void left() {
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(3, 255);
  analogWrite(9, 255);
  digitalWrite(inab, 1);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 0);
  digitalWrite(indb, 1);
  digitalWrite(inaf, 1);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 0);
  digitalWrite(indf, 1);
}

void right() {
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(3, 255);
  analogWrite(9, 255);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 1);
  digitalWrite(incb, 1);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 1);
  digitalWrite(incf, 1);
  digitalWrite(indf, 0);
}

void stop_bot() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 0);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 0);
  digitalWrite(indf, 0);
}

void forward_left() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 1);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 0);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 1);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 0);
  digitalWrite(indf, 0);
}

void forward_right() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 1);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 1);
  digitalWrite(indf, 0);
}

void backward_left() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 1);
  digitalWrite(incb, 0);
  digitalWrite(indb, 0);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 1);
  digitalWrite(incf, 0);
  digitalWrite(indf, 0);
}

void backward_right() {
  analogWrite(5, th);
  analogWrite(6, th);
  analogWrite(3, th);
  analogWrite(9, th);
  digitalWrite(inab, 0);
  digitalWrite(inbb, 0);
  digitalWrite(incb, 0);
  digitalWrite(indb, 1);
  digitalWrite(inaf, 0);
  digitalWrite(inbf, 0);
  digitalWrite(incf, 0);
  digitalWrite(indf, 1);
}
