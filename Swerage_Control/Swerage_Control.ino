void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(A5, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
//  digitalWrite(A0, 1);
//  digitalWrite(A1, 1);
  digitalWrite(A3, 1);
  Serial.begin(9600);
}

void loop() {
  if(!digitalRead(A5)) {
    digitalWrite(A3, 1);
    delay(5000);
  }
  else digitalWrite(A3, 0);
  if(!digitalRead(12)) {
    digitalWrite(A0, 1);
    delay(1000);
  }
  else digitalWrite(A0, 0);
  if(!digitalRead(2)) {
    digitalWrite(A1, 1);
    delay(1000);
  }
  else digitalWrite(A1, 0);
  Serial.print(digitalRead(A5));
  Serial.print(digitalRead(2));
  Serial.println(digitalRead(12));

}
