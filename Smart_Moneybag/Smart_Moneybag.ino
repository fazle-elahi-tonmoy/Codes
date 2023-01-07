#define IR_receiver A0
#define buzzer_pin 6
#define led_pin A1
#define mid_value 950
#define alarm_time 3  //alarm on time
#define button 2

bool theif = 0, reading = 0, lock = 1;

int alarm_freq = 2000;
uint32_t timer, timer2, timer3, timer4;
bool led_state = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  (theif) ? alarm() : noTone(buzzer_pin);
  led_blinking();
  if (millis() - timer4 > alarm_time * 60) theif = 0;
}
