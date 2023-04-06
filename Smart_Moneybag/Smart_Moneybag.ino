#include <EEPROM.h>
#define IR_receiver A0
#define buzzer_pin 6
#define IR_Tx A1
#define LED 13
#define mid_value 950
#define trigger_time 3 //seconds to trigger time
#define button 2
#define debug 0

bool theif = 0, reading = 0, lock = 0, trigger = 0;

int alarm_freq = 2000;
uint32_t timer, timer2, timer3, timer4;
bool led_state = 0;
byte password, button_read, pass_read;
bool decimal_point;

void setup() {
  pinMode(IR_Tx, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  password = EEPROM.read(0);
  Serial.println(password);
}

void loop() {
  (theif) ? alarm() : noTone(buzzer_pin);
  if (millis() - timer4 > trigger_time * 1000 && trigger) {
    theif = 1;
    trigger = 0;
  }
  IR_Testing();
  press_function();
}
