#include <BluetoothSerial.h>
#include <Arduino.h>
BluetoothSerial ESP_BT;

int ENA = 5;
int IN1 = 16;
int IN2 = 17;
int IN3 = 4;
int IN4 = 2;
int ENB = 15;
int Speed = 100;
char btSignal;

void setup() {
  Serial.begin(115200);
  ESP_BT.begin("BB-8");  // Bluetooth device name
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  ledcSetup(10, 5000, 8);
  ledcAttachPin(ENA, 10);
  ledcAttachPin(ENB, 10);
  ledcWrite(10, Speed);
}

void loop() {
  if (ESP_BT.available()) {
    btSignal = ESP_BT.read();
    Serial.println(btSignal);

    if (btSignal >= '0' && btSignal <= '9') {
      Speed = 100 + (btSignal - '0') * 17;
      Serial.println(Speed);
      ledcWrite(10, Speed);
    }

    else if (btSignal == 'F') motor(1, 1);
    else if (btSignal == 'B') motor(-1, -1);
    else if (btSignal == 'L') motor(-1, 1);
    else if (btSignal == 'R') motor(1, -1);
    else motor(0, 0);
  }
}

void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (a < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }


  if (b > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (b < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
