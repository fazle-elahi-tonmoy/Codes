void full_checkup() {
  bool state = 1;
  beatAvg = 0;
  const byte RATE_SIZE = 4;
  byte rates[RATE_SIZE];
  byte rateSpot = 0;
  long lastBeat = 0;
  float beatsPerMinute;
  double avered = 0;
  double aveir = 0;
  double sumirrms = 0;
  double sumredrms = 0;
  double ESpO2 = 90.0;  //初始值
  double FSpO2 = 0.7;   //filter factor for estimated SpO2
  double frate = 0.95;  //low pass filter for IR/red LED value to eliminate AC component
  int i = 0;
  int Num = 30;
  const int FINGER_ON = 7000, MINIMUM_SPO2 = 90.0;

  while (1) {
    alarm(state);
    long irValue = particleSensor.getIR();  //Reading the IR value it will permit us to know if there's a finger on the sensor or not
    if (irValue > FINGER_ON) {
      state = 0;
      if (checkForBeat(irValue) == true) {
        long delta = millis() - lastBeat;
        lastBeat = millis();
        beatsPerMinute = 60 / (delta / 1000.0);  //計算平均心跳
        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
          rates[rateSpot++] = (byte)beatsPerMinute;
          rateSpot %= RATE_SIZE;
          beatAvg = 0;
          for (byte x = 0; x < RATE_SIZE; x++) beatAvg += rates[x];
          beatAvg /= RATE_SIZE;
          beatAvg += 10;
        }
      }

      uint32_t ir, red;
      double fred, fir;
      particleSensor.check();  //Check the sensor, read up to 3 samples
      if (particleSensor.available()) {
        i++;
        ir = particleSensor.getFIFOIR();                        //讀取紅外線
        red = particleSensor.getFIFORed();                      //讀取紅光
        fir = (double)ir;                                       //轉double
        fred = (double)red;                                     //轉double
        aveir = aveir * frate + (double)ir * (1.0 - frate);     //average IR level by low pass filter
        avered = avered * frate + (double)red * (1.0 - frate);  //average red level by low pass filter
        sumirrms += (fir - aveir) * (fir - aveir);              //square sum of alternate component of IR level
        sumredrms += (fred - avered) * (fred - avered);         //square sum of alternate component of red level

        if ((i % Num) == 0) {
          double R = (sqrt(sumirrms) / aveir) / (sqrt(sumredrms) / avered);
          SpO2 = -23.3 * (R - 0.4) + 100;
          ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;     //low pass filter
          if (ESpO2 <= MINIMUM_SPO2) ESpO2 = MINIMUM_SPO2;  //indicator for finger detached
          if (ESpO2 > 100) ESpO2 = 99.9;
          //Serial.print(",SPO2="); Serial.println(ESpO2);
          sumredrms = 0.0;
          sumirrms = 0.0;
          SpO2 = 0;
          i = 0;
        }
        particleSensor.nextSample();  //We're finished with this sample so move to next sample
      }
      text("  " + String(beatAvg) + " BPM", 11, 02);
      if (beatAvg > 30) text("  " + String(ESpO2, 2) + "%  ", 11, 05);
      else text("  ---- %  ", 11, 05);
    }

    else {
      if (beatAvg > 30) {
        b_check = 0;
        SpO2 = ESpO2;
        last_checked_time = 0;
        lct = millis();
        checkup.updateAndReportParam("Body Check", b_check);
        checkup.updateAndReportParam("Pulse Value", beatAvg);
        checkup.updateAndReportParam("Oximeter Value", SpO2);
        checkup.updateAndReportParam("Last Checked", last_checked_time);
        oled.clear();
        return;
      }
      for (byte rx = 0; rx < RATE_SIZE; rx++) rates[rx] = 0;
      beatAvg = 0;
      rateSpot = 0;
      lastBeat = 0;
      avered = 0;
      aveir = 0;
      sumirrms = 0;
      sumredrms = 0;
      SpO2 = 0;
      ESpO2 = 90.0;
      state = 1;
      text("PLACE YOUR", 04, 02);
      text("  FINGER  ", 04, 05);
      oled.clear();
    }
  }
}