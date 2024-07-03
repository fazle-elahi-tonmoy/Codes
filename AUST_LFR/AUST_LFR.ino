#include <EEPROM.h>
#define lms 5
#define lmf 6
#define lmb 7
#define rmf 8
#define rmb 9
#define rms 10
#define sw 12
#define led 13

int s[6], sum;
int base[6] = { 1, 2, 4, 8, 16, 32 };
int threshold[6], maximum[6], minimum[6], sensor;

int lsp = 12, rsp = 12, tsp = 100;
int pos;
char turn = 's', side = 'l', cross = 's';
int node_delay = 10;
unsigned long t1, t2;

void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  for (byte i = 0; i < 6; i++) {
    threshold[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 6) * 4;
    minimum[i] = EEPROM.read(i + 12) * 4;
    Serial.println(String(minimum[i]) + " " + String(threshold[i]) + " " + String(maximum[i]) + " ");
  }
}

void loop() {
  int r = push(sw);
  if (r != 0) {
    if (r == 1) line_follow();
    else if (r == 2) cal();
    else if (r == 3)
      while (1) show_analog_value();
    else if (r == 4) motor(10 * lsp, 10 * rsp);
  }
}
