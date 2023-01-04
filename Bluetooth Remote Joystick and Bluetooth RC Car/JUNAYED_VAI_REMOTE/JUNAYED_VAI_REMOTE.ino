// tonmoy
#define n1 10
#define n2 9
#define n3 6
#define n4 8
#define power 7

char x = 's';


void setup() {

  pinMode(n1, INPUT);
  pinMode(n2, INPUT);
  pinMode(n3, INPUT);
  pinMode(n4, INPUT);
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);

  Serial.begin(9600);
}

void loop() {

  if (digitalRead(n1) == HIGH) {
    if (x != 'w') {
      Serial.write('w');
      x = 'w';
    }

  }
  else if (digitalRead(n2) == HIGH) {
    if (x != 'x') {
      Serial.write('x');
      x = 'x';
    }

  }
  else if (digitalRead(n3) == HIGH) {
    if (x != 'y') {
      Serial.write('y');
      x = 'y';
    }

  }
  else if (digitalRead(n4) == HIGH) {
    if (x != 'z') {
      Serial.write('z');
      x = 'z';
    }
  }
  else if (analogRead(A2) < 250) {
    if (x != 'l') {
      Serial.write('l');
      x = 'l';
    }
  }
  else if (analogRead(A2) > 750) {
    if (x != 'r') {
      Serial.write('r');
      x = 'r';
    }

  }
  else if (analogRead(A1) < 250) {
    if (x != 'f') {
      Serial.write('f');
      x = 'f';
    }

  }
  else if (analogRead(A1) > 750) {
    if (x != 'b') {
      Serial.write('b');
      x = 'b';
    }

  }
  else {
    if (x != 's') {
      Serial.write('s');
      x = 's';
    }
  }
  delay(10);
}
