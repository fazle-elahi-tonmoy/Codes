#define MIC1 A0  // bottom-left
#define MIC2 A1  // bottom-right
#define MIC3 A2  // top-right
#define MIC4 A3  // top-left
// Threshold to detect hit sound
const int threshold = 30;
// Speed of sound (cm/us)
const float SOUND_SPEED = 0.0343;
unsigned long t1, t2, t3, t4;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Failed!");
    while (1)
      ;
  }
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);
  radio.stopListening();
}
void loop() {

  if (analogRead(MIC1) > threshold || analogRead(MIC2) > threshold || analogRead(MIC3) > threshold || analogRead(MIC4) > threshold) {
    t1 = waitForHit(MIC1);
    t2 = waitForHit(MIC2);
    t3 = waitForHit(MIC3);
    t4 = waitForHit(MIC4);

    // Normalize times to first detection
    unsigned long tMin = min(min(t1, t2), min(t3, t4));
    t1 -= tMin;
    t2 -= tMin;
    t3 -= tMin;
    t4 -= tMin;

    // Convert times to distances
    float d1 = t1 * SOUND_SPEED;
    float d2 = t2 * SOUND_SPEED;
    float d3 = t3 * SOUND_SPEED;
    float d4 = t4 * SOUND_SPEED;

    char text[50];
    char buf1[10], buf2[10], buf3[10], buf4[10];

    dtostrf(d1, 0, 2, buf1);  // 0 = min width, 2 = decimal places
    dtostrf(d2, 0, 2, buf2);
    dtostrf(d3, 0, 2, buf3);
    dtostrf(d4, 0, 2, buf4);

    sprintf(text, "%s,%s,%s,%s;", buf1, buf2, buf3, buf4);

    radio.write(&text, sizeof(text));
    Serial.print("Data sent: ");
    Serial.println(text);
    delay(1000);
  }
}

unsigned long waitForHit(int pin) {
  while (true) {
    int val = analogRead(pin);
    if (val > threshold) {
      return micros();  // capture time in microseconds
    }
  }
}