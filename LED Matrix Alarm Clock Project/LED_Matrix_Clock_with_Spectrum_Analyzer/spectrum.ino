void spectrum() {
  for (int i = 0; i < 4; i++) lc.clearDisplay(i);
  while (!digitalRead(menu_button));
  while (digitalRead(menu_button)) {
    for (int i = 0; i < SAMPLES; i++) {
      int value = analogRead(0) - 512 ;
      vReal[i] = value / 8;
      vImag[i] = 0;
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    int step = (SAMPLES / 2) / xres;
    int c = 0;
    for (int i = 0; i < (SAMPLES / 2); i += step)
    {
      data_avgs[c] = 0;
      for (int k = 0 ; k < step ; k++) data_avgs[c] = data_avgs[c] + vReal[i + k];
      data_avgs[c] = data_avgs[c] / step;
      c++;
    }

    for (int i = 0; i < 32; i++)
    {
      data_avgs[i] = constrain(data_avgs[i], 0, 80);          // set max & min values for buckets
      data_avgs[i] = map(data_avgs[i], 0, 80, 0, yres);        // remap averaged values to yres
      yvalue = data_avgs[i];
      peaks[i] = peaks[i] - 1;  // decay by one light
      if (yvalue > peaks[i]) peaks[i] = yvalue ;
      yvalue = peaks[i];
      displayvalue = MY_ARRAY[yvalue];
      displaycolumn = i % 8;
      lc.setColumn(3 - (i / 8), displaycolumn, displayvalue);
    }
  }
  for (int i = 0; i < 4; i++) lc.clearDisplay(i);
  while (!digitalRead(menu_button));
}
