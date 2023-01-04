#include <Adafruit_Fingerprint.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("\n\n Adafruit finger detect test");
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()){
    Serial.println("Found fingerprint sensor!"); 
    fingerprint_statusCheck();
  } 
}

void loop()  // run over and over again
{
  getFingerPrint();
  delay(50);  //don't ned to run this at full speed.
}



