#define IR_receiver 14
const int buzzer_pin = 13;
const int led_pin = 15;
const int mid_value = 1000;
const int alarm_time = 3;  //alarm on time

bool theif = 0, reading = 0, lock = 1;

int alarm_freq = 2000;
uint32_t timer, timer2, timer3, timer4;
bool led_state = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  (theif) ? alarm() : noTone(buzzer_pin);
  led_blinking();
  if (timer4 - millis() > 180000) theif = 0;
}



