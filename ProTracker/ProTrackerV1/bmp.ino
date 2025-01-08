void showBMP(const char *filename, int16_t x, int16_t y) {
  File bmpFile;
  int bmpWidth, bmpHeight;
  uint8_t bmpDepth;
  uint32_t rowSize;
  uint8_t sdbuffer[3 * 20];
  uint16_t w, h, row, col;
  uint8_t r, g, b;
  bool goodBmp = false;
  bool flip = true;

  uint32_t pos = 0, startTime = millis();
  if ((x >= tft.width()) || (y >= tft.height())) return;

  // SD কার্ড থেকে BMP ফাইল ওপেন করুন
  bmpFile = SD.open(filename, FILE_READ);
  if (!bmpFile) {
    Serial.println("BMP file not found!");
    return;
  }

  // BMP হেডার পড়ুন
  if (read16(bmpFile) == 0x4D42) {  // BMP ফাইল সিগনেচার
    uint32_t fileSize = read32(bmpFile);
    read32(bmpFile);                            // রিজার্ভড
    uint32_t bmpImageoffset = read32(bmpFile);  // ইমেজ ডেটার শুরু পজিশন
    uint32_t headerSize = read32(bmpFile);
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);

    if (read16(bmpFile) == 1) {                          // প্লেনস
      bmpDepth = read16(bmpFile);                        // কালার ডেপথ
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) {  // 24-বিট BMP
        goodBmp = true;
        rowSize = (bmpWidth * 3 + 3) & ~3;

        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width()) w = tft.width() - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        for (row = 0; row < h; row++) {
          uint32_t rowPosition = bmpImageoffset + (flip ? bmpHeight - 1 - row : row) * rowSize;
          if (bmpFile.position() != rowPosition) {
            bmpFile.seek(rowPosition);
          }
          for (col = 0; col < w; col++) {
            bmpFile.read(sdbuffer, 3);
            b = sdbuffer[0];
            g = sdbuffer[1];
            r = sdbuffer[2];
            tft.drawPixel(x + col, y + row, tft.color565(r, g, b));
          }
        }
      }
    }
  }
  bmpFile.close();
  if (!goodBmp) Serial.println("BMP format not recognized.");
}

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();  // LSB
  ((uint8_t *)&result)[1] = f.read();  // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();  // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();  // MSB
  return result;
}

void drawImage(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *data) {
  tft.startWrite();               // Start writing to the display
  tft.setAddrWindow(x, y, w, h);  // Define the area to draw the image

  for (int16_t i = 0; i < w * h; i++) {
    uint16_t color = pgm_read_word(&data[i]);  // Read RGB565 data from PROGMEM
    tft.pushColor(color);                      // Send the color to the display
  }

  tft.endWrite();  // End the drawing operation
}
