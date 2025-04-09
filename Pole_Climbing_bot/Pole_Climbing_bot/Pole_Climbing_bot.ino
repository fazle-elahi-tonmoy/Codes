#include "BluetoothSerial.h"
#include <ESP32Servo.h>
#include <ZMPT101B.h>
Servo base, arm;
BluetoothSerial ESP_BT;
ZMPT101B voltageSensor(33, 50.0);

//AC Voltage Measurement
#define VREF 3.3             // ESP32 ADC Reference Voltage
#define ADC_RESOLUTION 4095  // ESP32 12-bit ADC
#define NUM_SAMPLES 20       // Number of samples for averaging
#define SENSITIVITY 480.0f

// Motor Pins
#define ENA 5  // PWM pin for speed control
#define IN1 18
#define IN2 19
#define IN3 21
#define IN4 22
#define ENB 23  // PWM pin for speed control

uint32_t timer;
int armMove = 0, armPos = 90;


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  ESP_BT.begin("PoleRobo");  // ESP32 Bluetooth name
  Serial.begin(115200);      // Start Serial Monitor
  motor(0, 0);
  updateSpeed(50);
  base.attach(27);
  arm.attach(25);
  base.write(90);
  arm.write(90);
  voltageSensor.setSensitivity(SENSITIVITY);
  timer = millis();
}

void loop() {
  if (ESP_BT.available()) {
    char x = ESP_BT.read();
    if (x == 'F') motor(1, 1);
    else if (x == 'B') motor(-1, -1);
    else if (x == 'S') motor(0, 0);
    else if (x == 'T') armMove = -1;
    else if (x == 'D') armMove = 1;
    else if (x == 'N') armMove = 0;
    else if (x >= 'k' && x <= 't') base.write(map((x - 'k'), 0, 9, 10, 180));
    else if (x >= '0' && x <= '9') updateSpeed(map((x - '0'), 0, 9, 50, 255));
  }
  
  if (millis() - timer > 5000) {
    timer = millis();
    int voltage = voltageSensor.getRmsVoltage();
    sendString(String(voltage));
  }

  if (armMove) {
    if (armMove == 1 && armPos < 150) {
      armPos++;
      arm.write(armPos);
      delay(10);
    }
    if (armMove == -1 && armPos > 30) {
      armPos--;
      arm.write(armPos);
      delay(10);
    }
  }
}


void updateSpeed(int a) {
  analogWrite(ENA, a);
  analogWrite(ENB, a);
}
