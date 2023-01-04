#include<NewPing.h>
int sf;
int forward_delay = 100;
NewPing sonar(2, 3, 100);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, INPUT);
  pinMode(9, INPUT);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(4, 1);
  digitalWrite(5, 0);

}

void loop() {
  if (digitalRead(9) == HIGH) {
    Serial.write('X');
    delay(50);
    Serial.write('S');
    delay(50);
    Serial.write('2');
    delay(50);
    while (digitalRead(9) == HIGH) {
      if (digitalRead(6) == HIGH) {
        while (digitalRead(6) == HIGH) {
          Serial.write('F');
          delay(50);
          sf = sonar.ping_cm();
          if (sf > 5 && sf <= 50) {
            delay(forward_delay);
            Serial.write('S');
            delay(50);
            break;
          }
        }
        Serial.write('9');
        delay(50);
        for (int i = 0; i <= 5 ; i++) {
          Serial.write('R');
          delay(50);
          if (digitalRead(6) == LOW) break;
        }
        Serial.write('S');
        delay(50);
        if (digitalRead(6) == HIGH) Serial.write('x');
      }
    }
  }
}

