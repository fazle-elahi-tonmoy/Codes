void drawImage(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *data) {
  tft.startWrite();               // Start writing to the display
  tft.setAddrWindow(x, y, w, h);  // Define the area to draw the image

  for (int16_t i = 0; i < w * h; i++) {
    uint16_t color = pgm_read_word(&data[i]);  // Read RGB565 data from PROGMEM
    tft.pushColor(color);                      // Send the color to the display
  }

  tft.endWrite();  // End the drawing operation
}
