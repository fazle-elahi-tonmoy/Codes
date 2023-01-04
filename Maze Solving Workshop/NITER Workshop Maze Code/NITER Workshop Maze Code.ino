#include <EEPROM.h>
#define spl 25
#define spr 25
#define tsp 200
#define stop_timer 500
#define u_turn_timer 500
#define node_delay 400
char turn = 's', cross = 's', rule = 'l';
const byte lmf = 9, lmb = 8, rmf = 7, rmb = 6, lms = 10, rms = 5, button = 3, led = 13;
int s[6];
int mid[6] = { 505, 350, 332, 357, 420, 445 };
int base[6] = { 1, 2, 4, 8, 16, 32 };
int sensor, sum;
unsigned long m1, m2;
bool inverse = 0;
byte path[50] = {};
byte counter = 0;
void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  byte x = press(button);
  if (x != 0) {
    if (x == 1) maze_scan();
    else if (x == 2) maze_solve(0);
    else if (x == 3) maze_solve(1);
    else if (x == 4)
      while (1) show_analog();
    else if (x == 5)
      while (1) show_digital();
    else if (x == 6) motor(10 * spl, 10 * spr);
    else if (x == 7) {
      memory_recall();
      for (byte i = 0;; i++) {
        Serial.print(path[i]);
        Serial.print(" ");
        if (path[i] == 5) break;
      }
    }

    else if (x == 10) memory_clear();
  }
}
