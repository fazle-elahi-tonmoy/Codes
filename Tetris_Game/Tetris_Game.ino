#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define WIDTH 64    // OLED display width, in pixels
#define HEIGHT 128  // OLED display height, in pixels


Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const char pieces_S_l[2][2][4] = { { { 0, 0, 1, 1 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 1, 1, 0, 0 } } };
const char pieces_S_r[2][2][4] = { { { 1, 1, 0, 0 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 0, 0, 1, 1 } } };
const char pieces_L_l[4][2][4] = { { { 0, 0, 0, 1 }, { 0, 1, 2, 2 } }, { { 0, 1, 2, 2 }, { 1, 1, 1, 0 } }, { { 0, 1, 1, 1 }, { 0, 0, 1, 2 } }, { { 0, 0, 1, 2 }, { 1, 0, 0, 0 } } };
const char pieces_Sq[1][2][4] = { { { 0, 1, 0, 1 }, { 0, 0, 1, 1 } } };
const char pieces_T[4][2][4] = { { { 0, 0, 1, 0 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 1, 0, 1, 1 } }, { { 1, 0, 1, 1 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 0, 0, 1, 0 } } };
const char pieces_l[2][2][4] = { { { 0, 1, 2, 3 }, { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 }, { 0, 1, 2, 3 } } };
const short MARGIN_TOP = 19;
const short MARGIN_LEFT = 3;
const short SIZE = 5;
const short TYPES = 6;


int left = 11;
int right = 9;
int change = 12;
int speed = 10;





void setup() {
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(change, INPUT_PULLUP);
  pinMode(speed, INPUT_PULLUP);
  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }


  oled.setRotation(1);
  oled.clearDisplay();
  drawLayout();
  oled.display();
  randomSeed(analogRead(32)/4);
  nextType = random(TYPES);
  generate();
  timer = millis();
}


void loop() {


  if (millis() - timer > interval) {
    checkLines();
    refresh();
    if (nextCollision()) {
      for (short i = 0; i < 4; i++)
        grid[pieceX + piece[0][i]][pieceY + piece[1][i]] = 1;
      generate();
    }

    else pieceY++;
    timer = millis();
  }


  if (!digitalRead(left)) {
    if (b1) {
      if (!nextHorizontalCollision(piece, -1)) {
        pieceX--;
        refresh();
      }
      b1 = false;
    }
  } else b1 = true;


  if (!digitalRead(right)) {
    if (b2) {
      if (!nextHorizontalCollision(piece, 1)) {
        pieceX++;
        refresh();
      }
      b2 = false;
    }


  } else b2 = true;

  (!digitalRead(speed)) ? interval = 20 : interval = 400;

  if (!digitalRead(change)) {
    if (b3) {
      if (rotation == getMaxRotation(currentType) - 1 && canRotate(0)) rotation = 0;
      else if (canRotate(rotation + 1)) rotation++;
      copyPiece(piece, currentType, rotation);
      refresh();
      b3 = false;
      delayer = millis();
    }
  } else if (millis() - delayer > 50) b3 = true;
}