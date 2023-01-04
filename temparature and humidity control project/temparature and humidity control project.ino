#include <SimpleDHT.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SimpleDHT22 dht22(8);

int e = 0;
int f = 0;
int heater = 7;
int fan = 13;

void display_function() {   //instead of typing it again and again, why dont you call a function??!!
  lcd.clear();
  lcd.print("Temp ");
  lcd.print(f);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humi ");
  lcd.print(e);
  lcd.print(" %");
  lcd.noCursor();
}

void check_system() {  //a manual function for updating the value of humidity. just recall it instead of typing the whole part again and again!
  float temperature = 0;
  float humidity = 0;
  dht22.read2(&temperature, &humidity, NULL);
  delay(2500);
  e = humidity;
  f = temperature;
}

void setup() {
  lcd.begin(16, 2);
  pinMode(heater, OUTPUT);
  pinMode(fan, OUTPUT);
  check_system();
  display_function();

  if (e >= 30) {      //forcing the system to pull down humidity just for once so that it can boot up the loop
    digitalWrite(fan, 1);
    digitalWrite(heater, 0);
    while (1) {
      check_system();
      display_function();     //refreshing the lcd display
      if (e <= 25) break;     // forcing the system to go down below 25% humidity so that heater can activate as per logic in the loop for below 30%
    }
    digitalWrite(fan, 0);
  }
}

void loop() {
  check_system();

  if (e <= 30) {
    //first the heater starts
    digitalWrite(fan, 0);
    digitalWrite(heater, 1);
    while (1) {
      check_system();
      display_function();
      if (e >= 50) break;
    }

    //here comes the second task where fan starts
    digitalWrite(fan, 1);
    digitalWrite(heater, 0);
    while (1) {
      check_system();
      display_function();
      if (e <= 35) break;
    }
    digitalWrite(fan, 0);  //shutting down all the system and going to idle mode
  }

  else if (e >= 50) {                       // safety measurement if humidity goes automatically high in idle mode
    digitalWrite(fan, 1);
    digitalWrite(heater, 0);
    while (1) {
      check_system();
      display_function();
      if (e <= 35) break;
    }
    digitalWrite(fan, 0);
  }
}

