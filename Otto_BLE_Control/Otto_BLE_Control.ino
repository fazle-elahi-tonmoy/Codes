#include <Otto.h>
#include <EEPROM.h>

#define LEFTLEG 4
#define RIGHTLEG 5
#define LEFTFOOT 6
#define RIGHTFOOT 7
#define TRIG 8
#define ECHO 9
#define BLE_TX 11
#define BLE_RX 10
#define BUZZER 13
#define sw 2

#if defined(ARDUINO_ARCH_ESP32)
#include "BluetoothSerial.h"
String device_name = "Otto BT Esp32";
BluetoothSerial bluetooth;
#else
#include <SoftwareSerial.h>
String device_name = "Otto BT";
SoftwareSerial bluetooth(BLE_TX, BLE_RX);
#endif

int move_speed[] = { 3000, 2000, 1000, 750, 500, 250 };
int n = 2;
int ultrasound_threeshold = 10;
int v;
int ch;
int i;
int steps = 1;
int positions[] = { 90, 90, 90, 90 };
int8_t trims[4] = { 0, 0, 0, 0 };
unsigned long sync_time = 0;

bool calibration = false;
char x, command;

Otto Ottobot;

long ultrasound_distance() {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration / 58;
  return distance;
}

void setup() {
  Serial.begin(9600);
  Ottobot.init(LEFTLEG, RIGHTLEG, LEFTFOOT, RIGHTFOOT, true, BUZZER);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(sw, INPUT);
  bluetooth.begin(9600);
  bluetooth.print("AT+NAME" + device_name);
  Ottobot.home();
  v = 0;
}

void loop() {
  checkBluetooth();
  if (command == 'F') Ottobot.walk(steps, move_speed[n], FORWARD);
  else if (command == 'B') Ottobot.walk(steps, move_speed[n], BACKWARD);
  else if (command == 'L') Ottobot.turn(steps, move_speed[n], LEFT);
  else if (command == 'R') Ottobot.turn(steps, move_speed[n], RIGHT);
  else if (command == 'W') Avoidance();
  else if (command == 'U') UseForce();

  int r = push(sw);
  if (r) {
    Serial.println(r);
    Ottobot.playGesture(r - 1);
    delay(1000);
    Ottobot._moveServos(10, positions);
  }
}

void checkBluetooth() {
  if (bluetooth.available() > 0) {
    x = bluetooth.read();
    Serial.println(x);
    if (x >= '0' && x <= '9') {
      int speed = x - '0' + 1;
      n = speed / 2;
    }

    else if (x == 'X') Ottobot._moveServos(10, positions);
    else if (x == 'V') Ottobot.sing(S_superHappy);
    else if (x == 'S') {
      Ottobot.home();
      Ottobot._moveServos(10, positions);
      command = x;
    } else command = x;
  }
}

void Avoidance() {
  if (ultrasound_distance() <= ultrasound_threeshold) {
    Ottobot.playGesture(OttoConfused);
    for (int count = 0; count < 2; count++) {
      Ottobot.walk(1, move_speed[n], -1);  // BACKWARD
    }
    for (int count = 0; count < 4; count++) {
      Ottobot.turn(1, move_speed[n], 1);  // LEFT
    }
  }
  Ottobot.walk(1, move_speed[n], 1);  // FORWARD
}

void UseForce() {
  if (ultrasound_distance() <= ultrasound_threeshold) {
    Ottobot.walk(3, move_speed[n], -1);  // BACKWARD
  }
  if ((ultrasound_distance() > 10) && (ultrasound_distance() < 15)) {
    Ottobot.home();
  }
  if ((ultrasound_distance() > 15) && (ultrasound_distance() < 30)) {
    Ottobot.walk(3, move_speed[n], 1);  // FORWARD
  }
  if (ultrasound_distance() > 30) {
    Ottobot.home();
  }
}

int push(int pin_number) {
  int count = 0;
repeat:
  unsigned long int timer = 0;
  if (digitalRead(pin_number) == 1) {       //if the button is pressed
    delay(20);                              //debounce delay
    while (digitalRead(pin_number) == 1) {  //check if the button is still pressed
      delay(20);
      timer += 20;
    }
    if (timer != 0) {  //if the button was really pressed
      timer = 0;
      count++;
      while (digitalRead(pin_number) == 0) {
        delay(10);
        timer += 10;
        if (timer > 500) return count;
      }
      goto repeat;
    }
  } else return 0;
}
