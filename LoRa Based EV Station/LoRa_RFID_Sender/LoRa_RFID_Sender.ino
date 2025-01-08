#include <SPI.h>
#include <MFRC522.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
MFRC522 rfid(16, 5);                 //SDA PIN, RST PIN
byte cardValue[4];
String rfid_value = "";
#define ss 17
#define rst 15
#define dio0 4
#define relay 13
int charge_time = 1;
String LoRaData;
uint32_t charge_timer, wait_timer;
bool charge_stat = 0;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  delay(1000);
  SPI.begin();  // Init SPI bus
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6))
    ;
  LoRa.setSyncWord(0xA5);
  rfid.PCD_Init();  // Init MFRC522
  pinMode(0, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, 1);
  lcd.setCursor(0, 0);
  lcd.print("   LoRa Based   ");
  lcd.setCursor(0, 1);
  lcd.print("   EV Charger   ");
}

void loop() {
  if (rfid_read()) {
    lcd.setCursor(0, 0);
    lcd.print("      CARD      ");
    lcd.setCursor(0, 1);
    lcd.print("   VERIFYING    ");
    LoRa.beginPacket();
    LoRa.print(rfid_value);
    LoRa.endPacket();
    delay(1000);
    wait_timer = millis();
    while (1) {
      if (Serial.available()) {
        char x = Serial.read();
        if (x == 'Q') esp_restart();
      }
      if (millis() - wait_timer > 60000) {
        lcd.setCursor(0, 0);
        lcd.print("      HUB       ");
        lcd.setCursor(0, 1);
        lcd.print("     ERROR      ");
        delay(5000);
        home_screen();
        break;
      }
      int packetSize = LoRa.parsePacket();  // try to parse packet
      if (packetSize) {
        while (LoRa.available()) {
          LoRaData = LoRa.readString();
          Serial.println(LoRaData);
        }
        String id = getValue(LoRaData, ':', 0);
        String action = getValue(LoRaData, ':', 1);
        if (id == "HUB_2") {
          if (action == "start") {
            charge_time = 0;
            lcd.setCursor(0, 0);
            lcd.print("CHARGING ACTIVE ");
            lcd.setCursor(0, 1);
            lcd.print("Chg Time:      s");
            digitalWrite(relay, 0);
            charge_stat = 1;
          }

          else if (action == "stop") {
            charge_stat = 0;
            digitalWrite(relay, 1);
            lcd.setCursor(0, 0);
            lcd.print("    CHARGING    ");
            lcd.setCursor(0, 1);
            lcd.print("    COMPLETE    ");
            delay(3000);
            home_screen();
          }

          else {
            lcd.setCursor(0, 0);
            lcd.print("     CARD       ");
            lcd.setCursor(0, 1);
            lcd.print("     ERROR      ");
            delay(5000);
            home_screen();
          }
        }
        break;
      }
    }
  }


  if (!digitalRead(0)) system_test();
  if (Serial.available()) {
    char x = Serial.read();
    if (x == 'Q') esp_restart();
    if (x == 'S') system_test();
  }


  if (charge_stat) {
    if (millis() - charge_timer > 1000) {
      charge_timer = millis();
      charge_time++;
      time_print(charge_time);
    }
  }
}
