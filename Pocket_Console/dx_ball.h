byte playerX = 12;
const byte playerW PROGMEM = 20;
const byte brick_count PROGMEM = 34;
byte ballX = 30;
byte ballY = 50;
byte ballDirectionX = 1;
byte ballDirectionY = -1;
byte gameScore = 0;

byte enX[brick_count];
byte enY[brick_count];
bool enL[brick_count];

void bricks() {
  byte i = 6;
  for (byte j = 0; j < 10; j++)
    enX[j] = i + j * 12;
  i = 10;
  for (byte j = 10; j < 19; j++)
    enX[j] = i + (j - 10) * 12;
  i = 14;
  for (byte j = 19; j < 27; j++)
    enX[j] = i + (j - 19) * 12;
  i = 18;
  for (byte j = 27; j < 34; j++)
    enX[j] = i + (j - 27) * 12;
  i = 14;
  for (byte j = 0; j < 10; j++)
    enY[j] = i;
  i = 18;
  for (byte j = 10; j < 19; j++)
    enY[j] = i;
  i = 22;
  for (byte j = 19; j < 27; j++)
    enY[j] = i;
  i = 26;
  for (byte j = 27; j < 34; j++)
    enY[j] = i;
  for (byte j = 0; j < brick_count; j++)
    enL[j] = 1;
}
