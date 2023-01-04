int lmf=9, lmb=7, rmf=3, rmb=5;

void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
      char data =  Serial.read();
      Serial.println(data);
      if (data == 'F')      forward();
      else if (data == 'B') backward();
      else if (data == 'L' || data == 'G' || data == 'H') left();
      else if (data == 'R' || data == 'I' || data == 'J') right();
      else if (data == 'S') stop_bot();
    }

}

void forward(){
  digitalWrite(lmf, 1);
  digitalWrite(lmb, 0);
  digitalWrite(rmf, 1);
  digitalWrite(rmb, 0);
}

void backward(){
  digitalWrite(lmb, 1);
  digitalWrite(lmf, 0);
  digitalWrite(rmb, 1);
  digitalWrite(rmf, 0);
}

void left(){
  digitalWrite(lmb, 1);
  digitalWrite(lmf, 0);
  digitalWrite(rmf, 1);
  digitalWrite(rmb, 0);
}

void right(){
  digitalWrite(lmf, 1);
  digitalWrite(lmb, 0);
  digitalWrite(rmb, 1);
  digitalWrite(rmf, 0);
}

void stop_bot(){
  digitalWrite(lmf, 0);
  digitalWrite(lmb, 0);
  digitalWrite(rmf, 0);
  digitalWrite(rmb, 0);
}
