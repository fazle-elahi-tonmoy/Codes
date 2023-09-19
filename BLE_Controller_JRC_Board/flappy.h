#include "SSD1306Wire.h"  // legacy include: `#include "SSD1306.h"`
#include "images.h"
#include "fontovi.h"
SSD1306Wire display(0x3c, 21, 22);
#define DEMO_DURATION 3000
typedef void (*Demo)(void);
float zidx[4];
int prazan[4];
int razmak = 32;
int sirinaProlaza = 30;
int score = 0;
int stis = 0;
float fx = 30.00;
float fy = 22.00;
int smjer = 0;
unsigned long trenutno = 0;

int igra = 0;
int frame = 0;
unsigned long ton = 0;
int sviraj = 0;
