//#include <Wire.h>
//#include <Adafruit_SSD1306.h>

//Adafruit_SSD1306 display(4);

int lx, ly, rx, ry, l1, l2, r1, r2, lmb, rmb, pl, pr;
int i = 0, j = 0, tmpl = 9, tmpr = 9;
char tmp;

void setup() {
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
//  //  display.display();
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(WHITE);
  pinMode(2, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);

}

void loop() {
  button();
  //screen();
  command();
  
  //for display
//  if (digitalRead(2) == 0) {
//    tmpc = 0;
//    display.clearDisplay();
//    text("PAIRING", 2, 24);
//    display.display();
//    for (int i=88; i<=108; i+=10) {
//      text(".", i, 24);
//      display.display();
//      if (digitalRead(2) == 1) break;
//    }
//  }
//  else if (tmpc != digitalRead(2)) {
//    tmpc = digitalRead(2);
//    display.clearDisplay();
//    text("PAIRED!!!", 7, 24);
//    display.display();
//  }
  
  delay(100);
}//end of the loop

//void text(String t, int x, int y) {
//  display.setCursor(x, y);
//  display.print(t);
//}
