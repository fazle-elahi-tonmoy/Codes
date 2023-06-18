#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
MFRC522 rfid(10, 9);  //SDA PIN, RST PIN
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define button A3
#define relay 2
#define platform_sensor A0
#define side_sensor A1
#define front_sensor A2
#define long_press_timer 1000 //ms
#define rotation_adjustment 50 //ms
#define parking_scale 60  // in minutes scale

short int verify;
byte current_slot = 1;
bool vacancy[8] = { 1, 0, 1, 0, 1, 1, 1, 1 };
uint32_t parking_timer[8];

byte cardValue[4];
byte pass[8][4] = { { 0xE3, 0x8C, 0x21, 0xAA },
                    { 0x98, 0x98, 0x2F, 0x64 },
                    { 0x33, 0x40, 0xD3, 0xE5 },
                    { 0x23, 0x10, 0x2F, 0xE6 },
                    { 0x13, 0x8D, 0x3C, 0xE6 },
                    { 0x58, 0xE9, 0xDD, 0x64 },
                    { 0xB3, 0x8A, 0x80, 0xE5 },
                    { 0x03, 0xB7, 0x56, 0xE5 } };

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(platform_sensor, INPUT);
  pinMode(front_sensor, INPUT);
  pinMode(side_sensor, INPUT);
  digitalWrite(relay, 1);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
  lcd.blink();
  for (byte i = 0; i < 8; i++) vacancy[i] = EEPROM.read(i);
  starting_screen();
}

void loop() {
  verify = rfid_read();

  if (verify == -1) {
    text("Wrong Card Punched!!", 0, 2);
    lcd.setCursor(current_slot * 2 + 3, 0);
    delay(1000);
    starting_screen();
  }

  else if (verify > 0) {
    text("Card Punched: " + String(verify) + "     ", 0, 1);
    (vacancy[verify - 1]) ? text("Bringing Parking Lot", 0, 2) : text("Grabbing Your Car...", 0, 2);
    lcd.setCursor(current_slot * 2 + 3, 0);

    rotation(verify);

    if (vacancy[verify - 1]) parking_timer[verify - 1] = millis();
    else {
      //first calculate the parking time in minute format
      uint32_t meter = millis() - parking_timer[verify - 1];
      byte meter_save = meter / (parking_scale * 60000);
      if (meter_save == 0) meter_save = 1;

      //calculate the amount and show it to the user
      int amount = meter_save * 50;
      clean(2);
      text("Parking Time: " + String(meter_save) + "hr", 0, 2);
      text("Parking Fee: " + String(amount) + "taka", 0, 3);
      lcd.setCursor(current_slot * 2 + 3, 0);
      while (!push(button))
        ;

      // save the parking time into eeprom
      meter_save += EEPROM.read(verify + 7);
      EEPROM.write(verify + 7, meter_save);
    }

    vacancy[verify - 1] = !vacancy[verify - 1];
    EEPROM.write(verify - 1, vacancy[verify - 1]);
    starting_screen();
  }
  
  if (push(button) == 2) amount_display();
}
