void reading() {
  sensor = 0; //this is to refresh initial value
  for (int i = 0 ; i < 6 ; i++) {
    s[i] = analogRead(i);
    (s[i] > 512) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
  }
}

void show_the_value() {
  for (int i = 5 ; i >= 0 ; i++)
    Serial.print(String(s[i], 10) + " ");
  Serial.println();
}
