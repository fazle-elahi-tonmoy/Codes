unsigned long int m1=0, m2=0, m3=0, m4=0, m5=0, m6=0, m7=0;
int lmr = 6, lmf = 8, lmb = 9, lmcr = 7, rmr = 3, rmf = 5, rmb = 4, rmcr = 2, mmr = 17, mmf = 15, mmb = 14, mmcr = 16;
byte lmp = 0, rmp = 0, mmp = 0, lmrp = 0, rmrp = 0;
void setup() {

  pinMode(lmr, OUTPUT);
  pinMode(lmcr, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmr, OUTPUT);
  pinMode(rmcr, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(mmf, OUTPUT);
  pinMode(mmb, OUTPUT);
  pinMode(mmr, OUTPUT);
  pinMode(mmcr, OUTPUT);
  Serial.begin(9600);

}

void loop() {
//  Serial.print(lmp);
//  Serial.print(" ");
//  Serial.print(rmp);
//  Serial.print(" ");
//  Serial.print(mmp);
//  Serial.print(" ");
//  Serial.print(lmrp);
//  Serial.print(" ");
//  Serial.println(rmrp);
  if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.print(data);
    if (data == 'a') {
      if (lmrp != 1 && (m1 - m2 >= 200)) {
        lmrp = 1;
        digitalWrite(lmr, 1);
        digitalWrite(lmcr, 0);
        m2 = millis();
      }
      if (rmrp != 1 && (m1 - m3 >= 200)) {
        rmrp = 1;
        digitalWrite(rmr, 1);
        digitalWrite(rmcr, 0);
        m3 = millis();
      }
    }
    else if (data == 'b') {
      if (lmrp != 1 && (m1 - m2 >= 200)) {
        lmrp = 1;
        digitalWrite(lmr, 1);
        digitalWrite(lmcr, 0);
        m2 = millis();
      }
      if (rmrp != 0 && (m1 - m3 >= 200)) {
        rmrp = 0;
        digitalWrite(rmr, 0);
        digitalWrite(rmcr, 1);
        m3 = millis();
      }
    }
    else if (data == 'c') {
      if (rmrp != 1 && (m1 - m3 >= 200)) {
        rmrp = 1;
        digitalWrite(rmr, 1);
        digitalWrite(rmcr, 0);
        m3 = millis();
      }
      if (lmrp != 0 && (m1 - m2 >= 200)) {
        lmrp = 0;
        digitalWrite(lmr, 0);
        digitalWrite(lmcr, 1);
        m2 = millis();
      }
    }
    else if (data == 'd') {
      if (rmp != 1 && (m1 - m4 >= 200)) {
        rmp = 1;
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        m4 = millis();
      }
      if (mmp != 1 && (m1 - m5 >= 300)) {
        mmp = 1;
        digitalWrite(mmf, 1);
        digitalWrite(mmb, 0);
        m5 = millis();
      }
      if (lmp != 1 && (m1 - m6 >= 200)) {
        lmp = 1;
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        m6 = millis();
      }
    }
    else if (data == 'g') {
      if (rmp != 1 && (m1 - m4 >= 200)) {
        rmp = 1;
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        m4 = millis();
      }
      if (mmp != 0 && (m1 - m5 >= 300)) {
        mmp = 0;
        digitalWrite(mmf, 0);
        digitalWrite(mmb, 1);
        m5 = millis();
      }
      if (lmp != 0 && (m1 - m6 >= 200)) {
        lmp = 0;
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        m6 = millis();
      }
    }
    else if (data == 'e') {
      if (rmp != 0 && (m1 - m4 >= 200)) {
        rmp = 0;
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        m4 = millis();
      }
      if (mmp != 1 && (m1 - m5 >= 300)) {
        mmp = 1;
        digitalWrite(mmf, 1);
        digitalWrite(mmb, 0);
        m5 = millis();
      }
      if (lmp != 0 && (m1 - m6 >= 200)) {
        lmp = 0;
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        m6 = millis();
      }
    }
    else if (data == 'f') {
      if (rmp != 0 && (m1 - m4 >= 200)) {
        rmp = 0;
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        m4 = millis();
      }
      if (mmp != 0 && (m1 - m5 >= 300)) {
        mmp = 0;
        digitalWrite(mmf, 0);
        digitalWrite(mmb, 1);
        m5 = millis();
      }
      if (lmp != 1 && (m1 - m6 >= 200)) {
        lmp = 1;
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        m6 = millis();
      }
    }
    else if (data == 's') {
      if (lmrp != 0 && (m1 - m2 >= 200)) {
        lmrp = 0;
        digitalWrite(lmr, 0);
        digitalWrite(lmcr, 1);
        m2 = millis();
      }
      if (rmrp != 0 && (m1 - m3 >= 200)) {
        rmrp = 0;
        digitalWrite(rmr, 0);
        digitalWrite(rmcr, 1);
        m3 = millis();
      }
      if (rmp != 0 && (m1 - m4 >= 200)) {
        rmp = 0;
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        m4 = millis();
      }
      if (mmp != 0 && (m1 - m5 >= 300)) {
        mmp = 0;
        digitalWrite(mmf, 0);
        digitalWrite(mmb, 1);
        m5 = millis();
      }
      if (lmp != 0 && (m1 - m6 >= 200)) {
        lmp = 0;
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        m6 = millis();
      }
    }
  }
  
  m1 = millis();
  if (m1 - m2 > 200) {
    digitalWrite(lmr, 0);
    digitalWrite(lmcr, 0);
  }
  if (m1 - m3 > 200) {
    digitalWrite(rmr, 0);
    digitalWrite(rmcr, 0);
  }
  if (m1 - m4 > 200) {
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 0);
  }
  if (m1 - m5 > 300) {
    digitalWrite(mmf, 0);
    digitalWrite(mmb, 0);
  }
  if (m1 - m6 > 200) {
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 0);
  }
}
