#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <EEPROM.h>

Servo nozzle;
BluetoothSerial SerialBT;

#define mq2 34
#define irL 35
#define irF 36
#define irR 39
#define pump 19
#define TRIG_PIN 17
#define ECHO_PIN 16
#define button 4


int lms = 14, lmf = 26, lmb = 27, rmf = 25, rmb = 33, rms = 32;
int speed = 200;
int threshold;
char x;
int fire[3];
bool fire_follow_mode = 0;

long duration;
int distance;

uint32_t sonar_timer, gas_timer;

void setup() {
  EEPROM.begin(8);
  Serial.begin(115200);
  SerialBT.begin("Fire Fighter");
  nozzle.attach(15);
  nozzle.write(90);
  threshold = EEPROM.read(0) * 16;
  Serial.println(threshold);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(mq2, INPUT);
  pinMode(button, INPUT_PULLUP);

  //for water pump
  pinMode(pump, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(21, OUTPUT);
  digitalWrite(18, 1);
  digitalWrite(21, 0);
  digitalWrite(pump, 0);

  //for sonar sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //for motor speed
  ledcSetup(10, 1000, 8);
  ledcSetup(11, 1000, 8);
  ledcAttachPin(lms, 10);
  ledcAttachPin(rms, 11);
  motor(0, 0);
  ledcWrite(10, speed);
  ledcWrite(11, speed);
}

void loop() {
  // Serial.println(digitalRead(button));
  int r = push();
  if (r) {
    Serial.println(r);
    if (r == 1) {
      fire_follow_mode = !fire_follow_mode;
      (fire_follow_mode) ? SerialBT.println("Fire Search Started!") : SerialBT.println("Fire Search Stopped!");
    }
    if (r == 2) {
      SerialBT.println("Pump Test");
      digitalWrite(pump, 1);
      delay(3000);
      digitalWrite(pump, 0);
    }
    if (r == 3) {
      while (!push()) {
        fire_read();
        for (byte i = 0; i < 3; i++) SerialBT.print(String(fire[i]) + " ");
        SerialBT.println();
        delay(1000);
      }
    }
    if (r == -1) {
      SerialBT.println("Calibrating...");
      fire_read();
      threshold = fire[1];
      EEPROM.write(0, threshold / 16);
      delay(10);
      EEPROM.commit();
      SerialBT.println("Done: " + String(fire[1]));
    }
  }

  if (fire_follow_mode) fire_follow();

  if (SerialBT.available()) {
    x = SerialBT.read();
    Serial.println(x);
  }
  motor_mode();
  if (millis() - sonar_timer > 30) {
    sonar_timer = millis();
    if (sonar() < 10) motor(0, 0);
  }

  if(digitalRead(mq2) && millis() - gas_timer>5000){
    gas_timer = millis();
    SerialBT.print("Gas Detected!");
  }
}
