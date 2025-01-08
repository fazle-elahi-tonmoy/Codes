void home_screen() {
  if (millis() - refresh_timer > 60) {
    refresh_timer = millis();
    display.clearDisplay();
    display.drawBitmap(4, 23, frames[frame], 32, 32, 1);
    text("LoRa", 60, 20);
    text(" HUB ", 54, 40);
    display.display();
    frame++;
    frame %= FRAME_COUNT;
  }
}

void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}