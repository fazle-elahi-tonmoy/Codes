#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IR 2
#define reset_pos 40
#define accept_pos 150
#define reject_pos 0

byte sequence = 0;
char password[4] = { '3', '2', '0', '3' };
char pass_input[4] = { 'A', 'B', 'C', 'D' };

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //three columns
byte motor_pins[4] = { 14, 15, 16, 17 };
int motor_delay[4] = { 700, 500, 500, 400 };
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 9, 10, 11, 12 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 4, 5, 6, 7 };     //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  for (byte i = 0; i < 4; i++) pinMode(motor_pins[i], OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  myservo.attach(3);
  myservo.write(reset_pos);
  pinMode(IR, INPUT);
  start_screen();
  pinMode(8, OUTPUT);
}

void loop() {
  // Serial.println(coin_detect());
  byte r = push(IR);
  if (r) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    CHECKING");
    lcd.setCursor(0, 1);
    lcd.print("    CURRENCY");
    bool flag = 0;
    uint32_t timer = millis();
    while (!coin_detect()) {
      if (millis() - timer > 5000) {
        flag = 1;
        break;
      }
    }

    if (flag) {
reject_protocol:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     PLEASE");
      lcd.setCursor(0, 1);
      lcd.print("   TRY AGAIN");
      myservo.write(reject_pos);
      delay(2000);
      for (int i = reject_pos; i < reset_pos; i++) {
        myservo.write(i);
        delay(5);
      }
      start_screen();
      return;
    }

    else {
selection:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SELECT  MEDICINE");
      lcd.setCursor(0, 1);
      lcd.print("Cancel-> Press D");
      int medicine_no;
      while (1) {
        char key = keypad.getKey();
        if (key) {
          if (key == 'D') goto reject_protocol;
          else if (key >= '1' && key <= '4') {
            medicine_no = key - '1';
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" SELECT MED ");
            lcd.print(key);
            lcd.print("?");
            lcd.setCursor(0, 1);
            lcd.print("A-> YES    NO<-B");
            break;
          }
        }
      }

      while (1) {
        char key = keypad.getKey();
        if (key == 'A') break;
        else if (key == 'B') goto selection;
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   DISPOSING");
      lcd.setCursor(0, 1);
      lcd.print("   MEDICINES");
      for (int i = reset_pos; i < accept_pos; i++) {
        myservo.write(i);
        delay(5);
      }
      motor_run(medicine_no);
      delay(1000);
      for (int i = accept_pos; i > reset_pos; i--) {
        myservo.write(i);
        delay(5);
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     PLEASE");
      lcd.setCursor(0, 1);
      lcd.print(" TAKE  MEDICINE");
      delay(2000);
    }
    start_screen();
  }
  unlock();
}
