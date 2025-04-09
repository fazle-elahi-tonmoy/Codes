bool game_pause() {
  while (1) {
    display.clearDisplay();
    display.setTextSize(2);
    text("GAME PAUSE", 04, 12);
    display.setTextSize(1);
    text("             RESUME", 04, 55);
    text("EXIT", 04, 55);
    display.display();
    if (push(l1)) return 1;
    else if (push(r1)) return 0;
  }
}

bool game_over(int a) {
  bool menu = 0;
  for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
  while (1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    text("GAME OVER!", 04, 0);
    text("SCORE:" + String(a), 04, 25);
    display.setTextSize(1);
    text("         PLAY AGAIN", 04, 55);
    text("EXIT", 04, 55);
    display.display();
    if (push(l1)) {
      menu = 1;
      break;
    } else if (push(r1)) {
      menu = 0;
      break;
    }
  }
  display.setTextSize(2);
  return menu;
}