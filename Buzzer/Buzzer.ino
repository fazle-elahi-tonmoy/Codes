#define reset_button 13

int led[10] = { 15, 4, 16, 17, 5, 18, 19, 21, 22, 23 };
int button[5] = { 14, 27, 26, 25, 33 };
bool reset = 0;


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) pinMode(button[i], INPUT);
  for (int i = 0; i < 10; i++) {
    pinMode(led[i], OUTPUT);
    (i % 2) ? digitalWrite(led[i], 0) : digitalWrite(led[i], 1);
  }
  pinMode(reset_button, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(button[i]) && !reset) {
      digitalWrite(led[(i * 2) + 1], 1);
      digitalWrite(led[i * 2], 0);
      reset = 1;
      Serial.print(i + 1);
      Serial.println(" Button Pressed!");
    }
  }

  if (!digitalRead(reset_button)) {
    for (int i = 0; i < 10; i++) {
      (i % 2) ? digitalWrite(led[i], 0) : digitalWrite(led[i], 1);
    }
    reset = 0;
  }

  // for(int i=0; i<5; i++){
  //   int button_val = digitalRead(button[i]);
  //   Serial.print(String(button_val) + " ");
  // }
  // Serial.println();
}
