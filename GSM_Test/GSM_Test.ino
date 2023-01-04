#include <SoftwareSerial.h>
bool alarm = 1;
uint32_t updt;
byte pipe1 = 16;

//Create software serial object to communicate with A6
SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and A6
  mySerial.begin(9600);

  Serial.print("Initializing");
  for (byte i = 0; i < 5; i++) {
    for (byte i = 0; i < 6; i++) {
      digitalWrite(13, !digitalRead(13)); delay(100);
    }
    delay(1000); Serial.print(".");
  }
  Serial.println();

  pinMode(pipe1, INPUT_PULLUP);

  starting_sequence();
}

void loop()
{
  if (digitalRead(pipe1) && alarm) {
    for (byte i = 0; i < 4; i++) {
      digitalWrite(13, !digitalRead(13)); delay(200);
    }
    for (byte i = 0; i < 2; i++) {
      delay(500); digitalWrite(13, !digitalRead(13));
    }
    Serial.println("alarm triggered!");
    send_text(); alarm = 0;
  }

  if (!digitalRead(pipe1)) {
    alarm = 1; delay(200);
  }

  if (updt - millis() > 1000) {
    updt = millis(); updateSerial();
  }
}
