#include <Servo.h>
Servo servo1, servo2;

unsigned long t1, t2;

int s1_min = 0, s1_max = 180, s1_pos = 0;
int s2_min = 40, s2_max = 150, s2_pos = 0;
bool dir = 1, dir2 = 1;


void setup() {
  servo1.attach(11);
  servo2.attach(10);
  Serial.begin(9600);
  s1_pos = s1_min;
  s2_pos = s2_min;
}

void loop() {
  if (millis() - t1 > 10) {
    t1 = millis();
    (dir) ? s1_pos++ : s1_pos--;
    if (s1_pos == s1_max) dir = 0;
    if (s1_pos == s1_min) dir = 1;
    servo1.write(s1_pos);
  }

  if (millis() - t2 > 20) {
    t2 = millis();
    (dir2) ? s2_pos++ : s2_pos--;
    if (s2_pos == s2_max) dir2 = 0;
    if (s2_pos == s2_min) dir2 = 1;
    servo2.write(s2_pos);
  }
}
