#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
#define ub 8
#define mb 9
#define db 10

short int pos[400] = {600, 400, 200, 000};
short int foodx, foody, dir = 3, len = 4, dl = 150;
bool eat = 1, s_b = 0;
unsigned long m81 = 0, m82 = 0;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  pinMode(ub, INPUT_PULLUP);
  pinMode(mb, INPUT_PULLUP);
  pinMode(db, INPUT_PULLUP);
}

void loop() {
  //  display.drawRect(30, 0, 98, 30, WHITE);
  //  display.display();
  if (eat == 1) food();
  draw();
  motion();
  button();
}

void draw() {
  for (short i = 0; i < len; i++) display.fillRect((pos[i] / 100) * 3, (pos[i] % 100) * 3, 3, 3, WHITE);
  for (short i = 0; i < len - 1; i++)
    if ((pos[i + 1] / 100) - (pos[i] / 100) <= 2 && (pos[i + 1] / 100) - (pos[i] / 100) >= -2 && (pos[i + 1] % 100) - (pos[i] % 100) <= 2 && (pos[i + 1] % 100) - (pos[i] % 100) >= -2)
      display.fillRect(((pos[i] / 100) + ((pos[i + 1] / 100) - (pos[i] / 100)) / 2) * 3, ((pos[i] % 100) + ((pos[i + 1] % 100) - (pos[i] % 100)) / 2) * 3, 3, 3, WHITE);
  display.fillRect(foodx * 3, foody * 3, 3, 3, WHITE);
  display.display(); display.clearDisplay();
}

void motion() {
  int posx = pos[0] / 100;
  int posy = pos[0] % 100;
  for (int i = len ; i > 0; i--) pos[i] = pos[i - 1];
  if (dir == 1) posx -= 2;
  else if (dir == 3) posx += 2;
  else if (dir == 2) posy -= 2;
  else if (dir == 4) posy += 2;
  if (posx > 40) posx = 0;
  else if (posx < 0) posx = 40;
  if (posy > 20) posy = 0;
  else if (posy < 0) posy = 20;

  pos[0] = posx * 100 + posy;
  if (pos[0] == 100 * foodx + foody) {
    eat = 1; len++;
  }
  for (short int i = 1; i < len ; i ++) if (pos[0] == pos[i]) len = 4;
}

void button() {
  m81 = m82 = millis();
  while (m82 - m81 < dl) {
    m82 = millis();
    if (digitalRead(ub) == LOW && s_b == 0) {
      dir++; s_b = 1;
    }
    if (digitalRead(db) == LOW && s_b == 0) {
      dir--; s_b = 1;
    }
    if (dir < 1) dir = 4;
    else if (dir > 4) dir = 1;
    
    if(digitalRead(ub) == HIGH && digitalRead(db) == HIGH) s_b = 0;
  }
}

void food() {
  eat = 0;
f:  foodx = (rand() % 20) * 2;
  foody = (rand() % 10) * 2;
  for (short int i = 0; i < len ; i ++) if (pos[i] == 100 * foodx + foody) goto f;
}
