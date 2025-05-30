short int pos[400] = { 600, 400, 200, 000 };
short int foodx, foody, dir = 3, len = 4, dl = 100;
bool eat = 1;
uint32_t st1;

void snake_game() {
  bool menu = 1;
  while (!push(r1)) {
    display.clearDisplay();
    display.setTextColor(1);
    display.setTextSize(2);
    text("GAME MODE?", 04, 0);
    text("   EASY   ", 04, 25);
    text("   HARD   ", 04, 50);
    (dl == 100) ? text(">>      <<", 04, 25) : text(">>      <<", 04, 50);
    display.display();
    if (digitalRead(er) == LOW) dl = 50;
    else if (digitalRead(el) == LOW) dl = 100;
  }

  while (1) {
    if (push(l1)) return;
    if (push(r1))
      if (game_pause()) {
        len = 4;
        return;
      }
    if (eat == 1) {
      food();
      digitalWrite(indicator, HIGH);
      for (int i = 2; i < 4; i++) playNote(selectionMelody[i], 50);
    }

    else digitalWrite(indicator, LOW);
    draw();
    if (millis() - st1 > dl) {
      motion();
      st1 = millis();
    }
    input();
    for (short int i = 1; i < len; i++)
      if (pos[0] == pos[i]) {
        digitalWrite(indicator, LOW);
        if (game_over(len - 4) == 1) {
          len = 4;
          return;
        }
        len = 4;
      }
  }
}

void draw() {
  for (short i = 0; i < len; i++) display.fillRect((pos[i] / 100) * 3, (pos[i] % 100) * 3, 3, 3, WHITE);
  for (short i = 0; i < len - 1; i++)
    if ((pos[i + 1] / 100) - (pos[i] / 100) <= 2 && (pos[i + 1] / 100) - (pos[i] / 100) >= -2 && (pos[i + 1] % 100) - (pos[i] % 100) <= 2 && (pos[i + 1] % 100) - (pos[i] % 100) >= -2)
      display.fillRect(((pos[i] / 100) + ((pos[i + 1] / 100) - (pos[i] / 100)) / 2) * 3, ((pos[i] % 100) + ((pos[i + 1] % 100) - (pos[i] % 100)) / 2) * 3, 3, 3, WHITE);
  display.fillRect(foodx * 3, foody * 3, 3, 3, WHITE);
  display.display();
  display.clearDisplay();
}

void motion() {
  int posx = pos[0] / 100;
  int posy = pos[0] % 100;
  for (int i = len; i > 0; i--) pos[i] = pos[i - 1];
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
    eat = 1;
    len++;
  }
}

void input() {
  input_read();
  if (joystick[0] == 1 || joystick[2] == -1) {
    if (dir != 1) dir = 3;
  }
  if (joystick[0] == -1 || joystick[2] == 1) {
    if (dir != 3) dir = 1;
  }
  if (joystick[1] == -1 || joystick[3] == 1) {
    if (dir != 2) dir = 4;
  }
  if (joystick[1] == 1 || joystick[3] == -1) {
    if (dir != 4) dir = 2;
  }
}

void food() {
  eat = 0;
f:
  foodx = (rand() % 20) * 2;
  foody = (rand() % 10) * 2;
  for (short int i = 0; i < len; i++)
    if (pos[i] == 100 * foodx + foody) goto f;
}


