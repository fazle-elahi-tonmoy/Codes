void setup() {
  for (int i = 22; i <= 50 ; i++)
    pinMode(i, OUTPUT);
  for (int i = 22; i <= 41 ; i++)
    digitalWrite(i, HIGH);
  for (int i = 44; i <= 50 ; i++)
    digitalWrite(i, LOW);
}

void loop() {
//    flashing("ROBO ADDA TEAM",2000);
//    clearscr();
    scrolling("ALAVI SADAB RAMISHA SHADMAN", 100);
}
