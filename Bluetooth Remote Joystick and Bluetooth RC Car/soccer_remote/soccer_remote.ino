int lx, ly, rx, ry, l1, l2, r1, r2, lmb, rmb, pl, pr;
int i = 0, j = 0, tmpl = 9, tmpr = 9;
char tmp;

void setup() {
  pinMode(2, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);

}

void loop() {
  button();
  //screen();
  command();  
  delay(10);
}//end of the loop
