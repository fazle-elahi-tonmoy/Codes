#include <HardwareSerial.h>
HardwareSerial SerialAT(2);  // Use UART2, GPIO16=RX, GPIO17=TX

String feedback = "";
String latitude, longitude, googleMapsLink;
String mobileNumber, smsContent;

uint32_t timer, initiator, sms_timer;
bool ready = 0, locationRead = 0, gpsMode = 0, sms_incoming = 0;
byte stage = 0, ignore = 0;

#define led 2
#define start_led 23
#define red 13
#define green 12
#define blue 14

void setup() {
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(start_led, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  Serial.begin(115200);
  SerialAT.begin(115200, SERIAL_8N1, 17, 16);
  initiator = timer = millis();
}

void loop() {
  if (stage) sendSMS(mobileNumber, googleMapsLink);
  if (ready) {
    delay(1000);
    SerialAT.println("AT+GPS=1");
    delay(1000);
    SerialAT.println("AT+CMGF=1");
    delay(1000);
    SerialAT.println("AT+CSMP=17,167,0,0");
    delay(1000);
    SerialAT.println("AT+CPMS=\"ME\",\"ME\",\"ME\"");
    gpsMode = 1;
    ready = 0;
    digitalWrite(start_led, 1);
    timer = millis();
  }

  if (millis() - timer > 10000 && gpsMode) {
    timer = millis();
    SerialAT.println("AT+LOCATION=2");
  }

  if (Serial.available()) {
    char x = Serial.read();
    SerialAT.print(x);
  }

  if (SerialAT.available()) {
    char c = SerialAT.read();
    if (c == '\n') {
      if (sms_incoming) {
        smsContent = feedback;
        Serial.println("Mobile Number: " + mobileNumber);
        Serial.println("SMS Content: " + smsContent + "");
        if (smsContent.startsWith("GPS")) {
          Serial.println("Command Accepted");
          stage = 1;
          digitalWrite(green, 1);
          sms_timer = millis();
        } else {
          digitalWrite(red, 1);
          delay(1000);
          digitalWrite(red, 0);
        }
        sms_incoming = 0;
      }
      if (locationRead) {
        if (feedback.startsWith("+LOCATION")) {
          digitalWrite(led, 0);
          googleMapsLink = "No GPS Available";
          locationRead = 0;
          Serial.println(googleMapsLink);
        }

        else if (ignore < 1) {
          ignore++;
          Serial.println("Ignored");
        }

        else {
          digitalWrite(led, 1);
          feedback.trim();
          googleMapsLink = "https://www.google.com/maps?q=" + feedback;
          locationRead = 0;
          ignore = 0;
          Serial.println(googleMapsLink);
        }
      }

      if (feedback.startsWith("AT+LOCATION")) locationRead = 1;
      if (feedback.startsWith("READY")) ready = 1;

      if (feedback.startsWith("+CMT")) {
        int firstQuote = feedback.indexOf('"');
        int secondQuote = feedback.indexOf('"', firstQuote + 1);
        mobileNumber = feedback.substring(firstQuote + 1, secondQuote);
        sms_incoming = 1;
        digitalWrite(blue, 1);
        delay(1000);
        digitalWrite(blue, 0);
      }

      if (feedback.startsWith("+CIEV")) {
        if (!feedback.indexOf("SMSFULL")) {
          digitalWrite(red, 1);
          delay(250);
          digitalWrite(red, 0);
          delay(250);
          digitalWrite(red, 1);
          delay(250);
          digitalWrite(red, 0);
          delay(250);
          digitalWrite(red, 1);
          delay(250);
          digitalWrite(red, 0);
        }
      }

      Serial.println(feedback);
      feedback = "";
    }

    else feedback += c;
  }

  if (!digitalRead(0)) {
    uint16_t timer = 0;
    delay(20);
    while (!digitalRead(0)) {
      delay(20);
      timer++;
      if (timer >= 100) break;
    }
    if (timer >= 100) {
      SerialAT.println("AT+CMGD=1,4");
      digitalWrite(green, 1);
      digitalWrite(blue, 1);
      delay(500);
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      delay(500);
      digitalWrite(green, 1);
      digitalWrite(blue, 1);
      delay(500);
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
    }
  }
}
