// Game definitions and variables
#define STREET_WIDTH 90        // street width at scene bottom, in pixels
#define STREETBORDER_WIDTH 10  // width of street border at scene bottom, in pixels
#define STREET_MINWIDTH 10     // minimum street width on horizont, in pixels
#define MAXLAPS 4              // game finishes after MAXLAPS
#define MAXSPEED 160            // global max speed
#define GRASSMINSPEED 4        // Min speed in grass
#define WARNINGWIDTH 16        // width of direction arrow at scene bottom, in pixels
#define WARNINGHEIGHT 16       // height of direction arrow at scene bottom, in pixels

unsigned long g_startMS;     // start of game
unsigned int g_distance;     // position on track
int g_playerPos;             // horizontal position of player
byte g_speed;                // current speed
byte g_laps;                 // number of finished laps
signed char g_curve;         // current curve
byte g_sprite;               // current player sprite
signed char g_streetMiddle;  // center of street

// track definition
typedef struct {
  byte segmentLength100;  // Length of segment. Do reduce memory consumtion segmentLength100 is byte and equal real segment lenght / 100
  byte segmentType;       // Bit pattern for segment type
} trackSegment;

#define TRACKLENGTH 8900  // Sum of all track segments in g_trackSegments (real segmentLenght=segmentLength100*100)
#define SEGMENTTYPE_DEFAULT 0
#define SEGMENTTYPE_LEFTCURVE 1
#define SEGMENTTYPE_RIGHTCURVE 2
#define SEGMENTTYPE_LEFTWARNING 32
#define SEGMENTTYPE_RIGHTWARNING 64
#define SEGMENTTYPE_FINISHGATE 128
#define MAXSEGMENTS 12
trackSegment g_trackSegments[MAXSEGMENTS] = {
  { 5, SEGMENTTYPE_DEFAULT },       // straight on
  { 7, SEGMENTTYPE_RIGHTWARNING },  // right warning
  { 10, SEGMENTTYPE_RIGHTCURVE },   // right
  { 12, SEGMENTTYPE_DEFAULT },      // straight on
  { 2, SEGMENTTYPE_LEFTCURVE },     // short curve change
  { 2, SEGMENTTYPE_RIGHTCURVE },    // short curve change
  { 5, SEGMENTTYPE_DEFAULT },       // straight on
  { 7, SEGMENTTYPE_LEFTWARNING },   // left warning
  { 10, SEGMENTTYPE_LEFTCURVE },    // left
  { 7, SEGMENTTYPE_RIGHTWARNING },  // right warning
  { 20, SEGMENTTYPE_RIGHTCURVE },   // long right curve
  { 2, SEGMENTTYPE_FINISHGATE },    // last tracksegment for finish gate
};

void moto_racing() {
  display.setTextSize(1);
  resetGame();
  while (1) {
    if (push(l1)) return;
    char strData[24];
    unsigned long startMS, endMS;
    static unsigned long lastPlayerMS = 0;
    static unsigned long lastBuzzerMS = 0;
    static unsigned int fps = 0;
    static int roll = 0;
    static int pitch = 0;
    // record start of frame
    startMS = millis();


    // ..............................................................................................................joystick control
    input_read();
    pitch = joystick[1];
    if (joystick[2] == -1) {
      if (roll < 45) roll++;
    }

    else if (joystick[2] == 1) {
      if (roll > -45) roll--;
    }

    else roll = 0;

    // change player sprite
    g_sprite = 0;
    if (roll < -1) {  // tilt to left
      g_sprite = 7 - (roll >> 3);
      if (g_sprite > (7 << 1) - 2) g_sprite = (7 << 1) - 2;
    }
    if (roll > 1) {  // tilt to right
      g_sprite = 1 + (roll >> 3);
      if (g_sprite > 6) g_sprite = 6;
    }

    // control player every 100ms
    if (millis() - lastPlayerMS > 100) {
      if (pitch == 1) {  // increase automatically
        if (g_speed > 140) g_speed++;
        else g_speed += 2;
        if (g_speed > MAXSPEED) g_speed = MAXSPEED;
      }

      else if (g_speed > 1) g_speed--;

      // Control left/right by roll
      g_playerPos += (1 + g_speed / 30) * 20 * roll / 90;

      // Drift in curves
      if (g_streetMiddle != 64) g_playerPos += (64 - g_streetMiddle) * (1 + g_speed / 60);

      if (g_playerPos < 16 / 2) g_playerPos = 16 / 2;
      if (g_playerPos > 128 - 16 / 2 - 1) g_playerPos = 128 - 16 / 2 - 1;

      if ((roll < -5) && (g_speed > GRASSMINSPEED)) g_speed--;  // reduce speed when tilt left
      if ((roll > 5) && (g_speed > GRASSMINSPEED)) g_speed--;   // reduce speed when tilt right

      lastPlayerMS = millis();
    }

    // clear display buffer
    display.clearDisplay();

    // End of game
    if (g_laps >= MAXLAPS) {
      display.setTextSize(2);
      display.setCursor(00, 24);
      display.print(F("   Finish   "));
      display.setTextSize(1);
      display.setCursor(0, 56);
      display.print(F("     in "));
      display.print((millis() - g_startMS) / 1000UL);
      display.print(F(" seconds"));
      display.display();
      while (!push(r1))
        if (push(l1)) return;
      display.clearDisplay();
      resetGame();
    }

    // draw sky
    drawSky();

    // draw rendered scene
    drawScene();

    // draw player sprite
    drawPlayer();

    // draw statistics data
    snprintf(strData, 24, "Lap%2d       %3d km/h", g_laps + 1, g_speed);
    display.setCursor(0, 0);
    display.print(strData);

    // show display buffer on screen
    display.display();

    if (millis() - lastBuzzerMS > 50) {
      if (g_speed < 1) noTone(buzzer);
      else tone(buzzer, 50 + g_speed * 5, 10);
      lastBuzzerMS = millis();
    }

    // calculate frames per second
    endMS = millis();
    if (endMS - startMS > 0) fps = 1000 / (endMS - startMS);
  }
}


int sin128(int degree) {
  degree = degree % 360;
  if (degree < 0) degree += 360;
  if (degree < 90) return pgm_read_byte_near(&g_sin128[degree]);
  if (degree < 180) return pgm_read_byte_near(&g_sin128[180 - degree]);
  if (degree < 270) return -(int)pgm_read_byte_near(&g_sin128[degree - 180]);
  return -(int)pgm_read_byte_near(&g_sin128[360 - degree]);
}

// draw player sprite
void drawPlayer() {
  int displayBeginX, displayBeginY;
  byte valueWhite, valueBlack;
  byte internalSpriteNbr;

  displayBeginX = g_playerPos - (16 >> 1);
  displayBeginY = 44;

  internalSpriteNbr = g_sprite;
  if (g_sprite > 6) {
    internalSpriteNbr -= (6);  // sprite number 7-12 and higher are only mirrored 1-6
    displayBeginX -= pgm_read_byte_near(&(g_spriteOffsetX[internalSpriteNbr]));
  } else {
    displayBeginX += pgm_read_byte_near(&(g_spriteOffsetX[internalSpriteNbr]));
  }

  // Draw sprite pixels
  for (int i = 0; i < 16; i++) {                                                            // every sprite line
    for (int j = 0; j < 2; j++) {                                                           // every 8 pixel per line (<16/8)
      valueWhite = pgm_read_byte_near(&(g_whiteSprites[internalSpriteNbr][(i << 1) + j]));  // ..][i * (16/8) + j]
      valueBlack = pgm_read_byte_near(&(g_blackSprites[internalSpriteNbr][(i << 1) + j]));
      for (int k = 0; k < 8; k++) {  // check bits from msb to lsb
        if (valueWhite & (0b10000000 >> k)) {
          if (g_sprite > 6)  // mirror sprite
            display.drawPixel(displayBeginX + 16 - ((j << 3) + k) - 1, displayBeginY + i, SSD1306_WHITE);
          else
            display.drawPixel(displayBeginX + (j << 3) + k, displayBeginY + i, SSD1306_WHITE);
        } else if (valueBlack & (0b10000000 >> k)) {
          if (g_sprite > 6)  // mirror sprite
            display.drawPixel(displayBeginX + 16 - ((j << 3) + k) - 1, displayBeginY + i, SSD1306_BLACK);
          else
            display.drawPixel(displayBeginX + (j << 3) + k, displayBeginY + i, SSD1306_BLACK);
        }
      }
    }
  }
}

// Some stars in the sky
void drawSky() {
  static byte offset = 0;
  byte screenOffset;

  // Move skycenter dependent on curve
  if (g_curve > 0) offset -= (g_speed >> 5);
  if (g_curve < 0) offset += (g_speed >> 5);

  screenOffset = (offset >> 1);
  display.drawPixel((screenOffset - 37) & 127, 16, SSD1306_WHITE);
  display.drawPixel((screenOffset + 59) & 127, 20, SSD1306_WHITE);
  display.drawPixel((screenOffset + 13) & 127, 15, SSD1306_WHITE);
  display.drawPixel((screenOffset + 55) & 127, 14, SSD1306_WHITE);
  display.drawPixel((screenOffset + 120) & 127, 19, SSD1306_WHITE);
  display.drawPixel((screenOffset - 74) & 127, 23, SSD1306_WHITE);
  display.drawPixel((screenOffset + 4) & 127, 10, SSD1306_WHITE);
  display.drawPixel((screenOffset + 35) & 127, 13, SSD1306_WHITE);
}

// draw street on grass (and finish gate and curve warnings if needed)
void drawScene() {
  byte currentStreetWidth;
  byte currentStreetBorderWidth;
  byte currentMiddle;
  unsigned int currentSegmentPosition;
  unsigned int currentSegmentLenght;
  unsigned int segmentSum;
  byte sceneHeight;
  byte currentTrackSegment;
  byte currentSegmentType;
  static unsigned long lastSlowdownMS = 0;
  signed char targetCurve;
  byte grassLeftBegin;
  byte grassLeftWidth;
  byte grassRightBegin;
  byte grassRightWidth;
  byte borderLeftBegin;
  byte borderLeftWidth;
  byte borderRightBegin;
  byte borderRightWidth;
  byte currentWidth;
  byte currentHeight;

  // half of screen
  sceneHeight = (64 >> 1);

  // increase player distance dependent on speed
  g_distance += g_speed >> 2;               // increase by 1/4th of speed
  if (g_distance >= TRACKLENGTH) g_laps++;  // count laps when finished
  g_distance = g_distance % TRACKLENGTH;    // modulo distance to complete track length

  // get current track segment
  currentTrackSegment = 0;
  currentSegmentLenght = 0;
  currentSegmentType = SEGMENTTYPE_DEFAULT;
  targetCurve = 0;
  segmentSum = 0;
  for (int i = 0; i < MAXSEGMENTS; i++) {
    if (g_distance < segmentSum + g_trackSegments[i].segmentLength100 * 100) {
      currentTrackSegment = i;
      currentSegmentLenght = g_trackSegments[i].segmentLength100 * 100;
      currentSegmentType = g_trackSegments[i].segmentType;

      if ((g_trackSegments[i].segmentType & SEGMENTTYPE_RIGHTCURVE) == SEGMENTTYPE_RIGHTCURVE) targetCurve = 100;
      if ((g_trackSegments[i].segmentType & SEGMENTTYPE_LEFTCURVE) == SEGMENTTYPE_LEFTCURVE) targetCurve = -100;
      // Position in current track segment
      currentSegmentPosition = g_distance - segmentSum;
      break;
    }
    segmentSum += g_trackSegments[i].segmentLength100 * 100;
  }

  // align curve to target curve of segment
  if (g_curve < targetCurve) {
    g_curve += g_speed >> 2;
    if (g_curve > targetCurve) g_curve = targetCurve;
  }
  if (g_curve > targetCurve) {
    g_curve -= g_speed >> 2;
    if (g_curve < targetCurve) g_curve = targetCurve;
  }
  for (int y = 0; y < sceneHeight; y++) {  // for each line in lower screen half
    // center of the road dependent on curve and fake "depth"
    currentMiddle = (128 >> 1) + g_curve / (y + 1);

    // width of street and border dependent on fake "depth"
    currentStreetWidth = ((STREET_WIDTH * (y + 1)) >> 5) + STREET_MINWIDTH;
    currentStreetBorderWidth = (STREETBORDER_WIDTH * (y + 1)) >> 5;

    // Draw grass
    grassLeftBegin = 0;
    grassLeftWidth = currentMiddle - currentStreetBorderWidth - (currentStreetWidth >> 1);
    grassRightBegin = currentMiddle + currentStreetBorderWidth + (currentStreetWidth >> 1);
    grassRightWidth = 128 - grassRightBegin;

    // fake "depth" oscillation with phase shifting (based on sin(frequenceScaler * (1.0f - (y/sceneHeight))^3 + distance*phaseshiftScaler) )
    if (sin128(((((31 - y) * (31 - y) * (31 - y)) >> 5) + g_distance)) > 0) {
      // Solid grass
      if (grassLeftWidth > 0) display.drawFastHLine(grassLeftBegin, y + sceneHeight, grassLeftWidth, SSD1306_WHITE);
      if (grassRightWidth > 0) display.drawFastHLine(grassRightBegin, y + sceneHeight, grassRightWidth, SSD1306_WHITE);
    } else {
      // Grass with simple dithering
      if (grassLeftWidth > 0)
        for (int k = grassLeftBegin; k < grassLeftBegin + grassLeftWidth; k++) {
          if ((k % 2 + y) % 2) display.drawPixel(k, y + sceneHeight, SSD1306_WHITE);
        }
      if (grassRightWidth > 0)
        for (int k = grassRightBegin; k < grassRightBegin + grassRightWidth; k++) {
          if ((k % 2 + y) % 2) display.drawPixel(k, y + sceneHeight, SSD1306_WHITE);
        }
    }

    // Draw street border
    borderLeftBegin = currentMiddle - currentStreetBorderWidth - (currentStreetWidth >> 1);
    borderLeftWidth = currentStreetBorderWidth;
    borderRightBegin = currentMiddle + (currentStreetWidth >> 1);
    borderRightWidth = currentStreetBorderWidth;

    // fake "depth" oscillation with phase shifting (use 4x faster frequency than grass)
    if (sin128(((((31 - y) * (31 - y) * (31 - y)) >> 5) + g_distance) << 2) > 0) {
      display.drawFastHLine(borderLeftBegin, y + sceneHeight, borderLeftWidth, SSD1306_WHITE);
      display.drawFastHLine(borderRightBegin, y + sceneHeight, borderRightWidth, SSD1306_WHITE);
    };

    // finish gate
    if ((currentSegmentType & SEGMENTTYPE_FINISHGATE) == SEGMENTTYPE_FINISHGATE) {
      // y-position of gate dependent on perspective y = sceneHeight * currentSegmentPosition / (currentSegmentLenght-currentSegmentPosition)
      if ((currentSegmentLenght - currentSegmentPosition > 0) && (y == (sceneHeight * currentSegmentPosition / (currentSegmentLenght - currentSegmentPosition)))) {
        // left pole
        display.drawFastVLine(borderLeftBegin, sceneHeight - 1, y + 1, SSD1306_WHITE);
        display.drawFastVLine(borderLeftBegin + 1, sceneHeight - 1, y + 1, SSD1306_BLACK);
        display.drawFastVLine(borderLeftBegin - 1, sceneHeight - 1, y + 1, SSD1306_BLACK);

        // right pole
        display.drawFastVLine(borderRightBegin + borderRightWidth - 1, sceneHeight - 1, y + 1, SSD1306_WHITE);
        display.drawFastVLine(borderRightBegin + borderRightWidth - 2, sceneHeight - 1, y + 1, SSD1306_BLACK);
        display.drawFastVLine(borderRightBegin + borderRightWidth, sceneHeight - 1, y + 1, SSD1306_BLACK);

        // top banner
        display.fillRect(borderLeftBegin, sceneHeight - ((y + 1) >> 1) - 1, borderRightBegin - borderLeftBegin + borderRightWidth, (y + 1) >> 1, SSD1306_WHITE);
      }
    }

    // right curve warning
    if ((currentSegmentType & SEGMENTTYPE_RIGHTWARNING) == SEGMENTTYPE_RIGHTWARNING) {
      // y-position dependent on perspective y = sceneHeight * currentSegmentPosition / (currentSegmentLenght-currentSegmentPosition)
      if ((currentSegmentLenght - currentSegmentPosition > 0) && (y == (sceneHeight * currentSegmentPosition / (currentSegmentLenght - currentSegmentPosition)))) {
        currentWidth = (y + 1) * WARNINGWIDTH / sceneHeight;
        if (currentWidth < 4) currentWidth = 4;
        currentHeight = (y + 1) * WARNINGHEIGHT / sceneHeight;
        if (currentHeight < 4) currentHeight = 4;
        // triangle to right
        display.fillTriangle(borderLeftBegin, sceneHeight + y - currentHeight / 2,
                             borderLeftBegin - currentWidth, sceneHeight + y - currentHeight,
                             borderLeftBegin - currentWidth, sceneHeight + y, SSD1306_BLACK);
        display.drawTriangle(borderLeftBegin, sceneHeight + y - currentHeight / 2,
                             borderLeftBegin - currentWidth, sceneHeight + y - currentHeight,
                             borderLeftBegin - currentWidth, sceneHeight + y, SSD1306_WHITE);
      }
    }

    // left curve warning
    if ((currentSegmentType & SEGMENTTYPE_LEFTWARNING) == SEGMENTTYPE_LEFTWARNING) {
      // y-position dependent on perspective y = sceneHeight * currentSegmentPosition / (currentSegmentLenght-currentSegmentPosition)
      if ((currentSegmentLenght - currentSegmentPosition > 0) && (y == (sceneHeight * currentSegmentPosition / (currentSegmentLenght - currentSegmentPosition)))) {
        currentWidth = (y + 1) * WARNINGWIDTH / sceneHeight;
        if (currentWidth < 4) currentWidth = 4;
        currentHeight = (y + 1) * WARNINGHEIGHT / sceneHeight;
        if (currentHeight < 4) currentHeight = 4;
        // triangle to left
        display.fillTriangle(borderRightBegin + borderRightWidth - 1, sceneHeight + y - currentHeight / 2,
                             borderRightBegin + borderRightWidth - 1 + currentWidth, sceneHeight + y - currentHeight,
                             borderRightBegin + borderRightWidth - 1 + currentWidth, sceneHeight + y, SSD1306_BLACK);
        display.drawTriangle(borderRightBegin + borderRightWidth - 1, sceneHeight + y - currentHeight / 2,
                             borderRightBegin + borderRightWidth - 1 + currentWidth, sceneHeight + y - currentHeight,
                             borderRightBegin + borderRightWidth - 1 + currentWidth, sceneHeight + y, SSD1306_WHITE);
      }
    }

    if (y == 20) {  // player line
      g_streetMiddle = currentMiddle;
      // Reduce speed in the grass
      if (millis() - lastSlowdownMS > 50) {
        if (((g_playerPos < borderLeftBegin) || (g_playerPos > grassRightBegin - 1))) {
          if (g_speed > 11) g_speed -= 8;
          else if (g_speed > GRASSMINSPEED) g_speed = GRASSMINSPEED;
        }
        lastSlowdownMS = millis();
      }
    }
  }
}

// initial game settings
void resetGame() {
  g_streetMiddle = 64;
  g_playerPos = g_streetMiddle;
  g_speed = 0;
  g_laps = 0;
  g_startMS = millis();
  g_distance = 0;
}
