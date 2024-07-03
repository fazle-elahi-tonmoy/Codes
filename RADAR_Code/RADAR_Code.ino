// Includes the Servo library
#include <Servo.h>
#include <NewPing.h>
// Defines Tirg and Echo pins of the Ultrasonic Sensor
NewPing Sonar(6, 7, 50);
// Variables for the duration and the distance
long duration;
int distance;

Servo Servo1;  // Creates a servo object for controlling the servo motor
Servo Servo2;  // Creates a servo object for controlling the servo motor
Servo Servo3;  // Creates a servo object for controlling the servo motor

bool sequence = 0, position = 0;
int i, pos = 50, p_min = 50, p_max = 150;


uint32_t timer = millis();

void setup() {
  Serial.begin(9600);
  Servo1.attach(9);   // Defines on which pin is the servo motor attached
  Servo2.attach(10);  // Defines on which pin is the servo motor attached
  Servo3.attach(11);  // Defines on which pin is the servo motor attached
  Servo1.write(90);
  Servo2.write(90);
  Servo3.write(pos);  // default position
  Serial.println("Waiting for Press");
  pinMode(12, INPUT_PULLUP);
  while (digitalRead(12))
    ;
  Serial.println("Robot Started!");
}
void loop() {
  (sequence == 0) ? i++ : i--;
  if (i > 165) sequence = 1;
  if (i < 15) sequence = 0;
  delay(30);
  Servo1.write(i);
  distance = Sonar.ping_cm();
  if (distance == 0) distance = 100;

  if (distance < 10) {  // trigger distance
    Servo2.write(i);
    position = 1;
    timer = millis();
  }

  Serial.print(i);         // Sends the current degree into the Serial Port
  Serial.print(",");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance);  // Sends the distance value into the Serial Port
  Serial.print(".");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing

  if (millis() - timer > 1000) position = 0;
  servo3_traccking();
}

void servo3_traccking() {
  if (position) {
    if (pos < p_max) Servo3.write(++pos);
  }

  else {
    if (pos > p_min) Servo3.write(--pos);
  }
}
