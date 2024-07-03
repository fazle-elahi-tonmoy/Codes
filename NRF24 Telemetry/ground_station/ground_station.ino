#define BLYNK_TEMPLATE_ID "TMPL64UbTPTLu"
#define BLYNK_TEMPLATE_NAME "Surveillance Drone"
#define BLYNK_AUTH_TOKEN "y_xs4q4uRWiv12Ry-h3i9JR5RSnozlFq"
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

RF24 radio(15, 13);  // CE, CSN
const byte addresses[6] = "00001";
int MQ2, MQ135, MQ7;
float temparature, humidity;
double data;

uint32_t timer;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  if (!radio.begin()) {
    Serial.println("Radio Failed!");
    while (1) {
      digitalWrite(2, 1);
      delay(100);
      digitalWrite(2, 0);
      delay(100);
    }
  }
  radio.openReadingPipe(0, addresses);  // 00002
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Blynk.begin(BLYNK_AUTH_TOKEN, "Tech Topia", "robotics");
  digitalWrite(2, 1);
  timer = millis();
}

void loop() {
  Blynk.run();
  if (radio.available()) {
    char value[10] = "";
    radio.read(&value, sizeof(value));
    char reading[10] = "";
    for (int i = 2; i < strlen(value); i++) reading[i - 2] = value[i];
    data = atof(reading);
    switch (value[0]) {
      case '1': MQ2 = data; break;
      case '2': MQ7 = data; break;
      case '3': MQ135 = data; break;
      case '4': temparature = data; break;
      case '5': humidity = data; break;
    }
  }

  if (millis() - timer > 2000) {
    timer = millis();
    Serial.println(String(MQ2) + "  " + String(MQ7) + "  " + String(MQ135) + "  " + String(temparature) + "  " + String(humidity));
    Blynk.virtualWrite(V0, temparature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, MQ2);
    Blynk.virtualWrite(V3, MQ135);
    Blynk.virtualWrite(V4, MQ7);
  }
}