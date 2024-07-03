void home_screen() {
  if (millis() - timer > 60) {
    timer = millis();
    display.clearDisplay();
    display.drawBitmap(32, 0, frames[frame], 64, 64, 1);
    display.display();
    frame = (frame + 1) % FRAME_COUNT;
  }
}