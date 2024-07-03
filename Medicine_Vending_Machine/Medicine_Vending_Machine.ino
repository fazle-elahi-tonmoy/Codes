void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SW 12

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { A0, A1, A2, A3 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 4, 5, 6, 7 };      //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(SW, INPUT_PULLUP);
  start_screen();
}

void loop() {


  byte r = push(SW);
  if (r) {
    if (r == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     PLEASE");
      lcd.setCursor(0, 1);
      lcd.print("SELECT  MEDICINE");
      while (1) {
        char key = keypad.getKey();
        if (key) {
          Serial.println(key);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("   DISPOSING");
          lcd.setCursor(0, 1);
          lcd.print("   MEDICINE ");
          lcd.print(key);
          break;
        }
      }
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     PLEASE");
      lcd.setCursor(0, 1);
      lcd.print(" TAKE  MEDICINE");
    }

    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     PLEASE");
      lcd.setCursor(0, 1);
      lcd.print("   TRY AGAIN");
    }
    delay(5000);
    start_screen();
  }
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

void start_screen() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("MEDICINE");
  lcd.setCursor(0, 1);
  lcd.print("VENDING  MACHINE");
}
