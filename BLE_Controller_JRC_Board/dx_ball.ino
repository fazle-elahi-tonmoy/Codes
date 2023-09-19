void DXBall() {
  bricks();
  while (1) {
    checkColision();
    checkButtonsGame();
    drawGame();
  }
}

void drawGame() {
  oled.clearDisplay();
  oled.setCursor(40, 0);
  oled.print(gameScore);
  oled.setCursor(2, 0);
  oled.print("Score:");
  oled.drawLine(0, 9, 127, 9, 1);
  oled.drawLine(0, 9, 0, 63, 1);
  oled.drawLine(127, 9, 127, 63, 1);
  oled.fillRect(playerX, 60, playerW, 2, 1);
  oled.fillCircle(ballX, ballY, 1, 1);

  for (int i = 0; i < brick_count; i++)
    if (enL[i] == 1)
      oled.fillRect(enX[i], enY[i], 8, 2, 1);

  oled.display();
}

void checkButtonsGame() {
  if (!digitalRead(down) && playerX > 1) playerX -= 2;
  if (!digitalRead(up) && playerX < 126 - playerW) playerX += 2;
}

void GameReset() {
  ballX = random(1, 126);
  ballY = 50;
  ballDirectionX = 1;
  ballDirectionY = -1;
  gameScore = 0;
  for (int i = 0; i < brick_count; i++)
    enL[i] = 1;
}

void gameOver() {
  oled.setTextColor(1);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setCursor(6, 0);
  oled.print(gameScore);
  oled.setCursor(6, 20);
  oled.print("GAME");
  oled.setCursor(6, 40);
  oled.print("OVER");
  oled.setTextSize(0);
  oled.display();
  while (digitalRead(SW))
    ;
  GameReset();
}

void checkColision() {
  if (ballX < 1 || ballX > 126)
    ballDirectionX = ballDirectionX * -1;
  if (ballY < 10)
    ballDirectionY = ballDirectionY * -1;

  if (ballY > 60 && ballX > playerX && ballX < playerX + playerW) {
    ballDirectionY = ballDirectionY * -1;
    // (ballX < (2 * playerX + playerW) / 2) ? ballDirectionX = -1 : ballDirectionX = 1;
  }


  for (int i = 0; i < brick_count; i++)
    if (ballX > enX[i] && ballX < enX[i] + 8 && ballY > enY[i] && ballY < enY[i] + 2 && enL[i] == 1) {
      ballDirectionY = ballDirectionY * -1;
      enL[i] = 0;
      gameScore++;
    }

  ballX = ballX + ballDirectionX;
  ballY = ballY + ballDirectionY;

  if (ballY > 64)
    gameOver();

  if (gameScore % brick_count == 0 && gameScore)
    GameReset();
}