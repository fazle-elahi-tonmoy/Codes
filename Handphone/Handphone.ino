#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(3, 2);  //A6 Tx & Rx is connected to Arduino #3 & #2
byte stage = 0;

byte button = 4;

String phone_number = "8801721519766";
char sms_content[] = "Help Me! I am in Trouble!";


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    mySerial.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());  //Forward what Software Serial received to Serial Port
  }
  byte r = push(button);
  if (r == 1) send_call(1);
  else if (r == 2) send_call(2);
  else if (r == 3) send_sms();
}

void updateSerial() {
  delay(500);
  while (mySerial.available()) {
    Serial.write(mySerial.read());  //Forward what Software Serial received to Serial Port
  }
}

void send_sms() {
  mySerial.println("AT");  //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+" + phone_number + "\"");  //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(sms_content);  //text content
  updateSerial();
  mySerial.write(26);
}

void send_call(byte i) {
  if (i == 1) mySerial.println("ATD+" + phone_number);  //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  else if (i == 2) mySerial.println("ATH");
  updateSerial();
}


byte push(byte pin) {
  byte count = 0;
here:
  uint32_t timer = 0;
  if (digitalRead(pin) == 0) {
    delay(20);  //debounce delay
    while (digitalRead(pin) == 0) {
      delay(20);
      timer += 20;
      digitalWrite(13, 1);
    }
    digitalWrite(13, 0);
    if (timer) {
      timer = 0;
      count++;
      while (digitalRead(pin) == 1) {
        delay(20);
        timer += 20;
        if (timer > 500) return count;
      }
      goto here;
    }
  }
  return 0;
}