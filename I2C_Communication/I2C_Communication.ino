#include <Wire.h>

void setup() {
  Serial.begin(9600);        // start serial for output
  Wire.begin(8);             // join I2C bus with address #8
  Wire.onReceive(response);  // register event
}

void loop() {
  if (Serial.available()) {
    String x = Serial.readString();  //carriage return
    int channel = x[0] - '0';
    String message = x.substring(2);
    Wire.beginTransmission(channel);
    for (byte i = 0; i < message.length(); i++) Wire.write(message[i]);
    // Wire.write((char)10);
    bool p = Wire.endTransmission();
    (p) ? Serial.println("Error!") : Serial.println("Successfull");
  }
}

void response() {
  while (Wire.available()) {  // loop through all but the last
    char c = Wire.read();     // receive byte as a character
    Serial.print(c);          // print the character
  }
}
