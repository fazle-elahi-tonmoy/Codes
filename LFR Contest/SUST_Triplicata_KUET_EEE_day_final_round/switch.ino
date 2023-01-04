int leftswitch() {
  if (digitalRead(rb) == LOW) {
    short int i = 0, temp = 0,  j;
a:  while (digitalRead(rb) == LOW) {
      delay(1);
      digitalWrite(12, HIGH);
      i++;
      int t = 0;
      while (digitalRead(lb) == LOW && digitalRead(rb) == LOW) {
        t++;
        delay(1);
        if (t > 100) {
          digitalWrite(13, HIGH);
          while (digitalRead(lb) == LOW && digitalRead(rb) == LOW);
          (digitalRead(lb) == LOW) ? j = 1 : j = 2;
          (digitalRead(lb) == LOW) ? digitalWrite(13, LOW) : digitalWrite(12, LOW);
          while (digitalRead(lb) == LOW || digitalRead(rb) == LOW);
          if (j == 1) {
            digitalWrite(12, LOW);
            delay(200);
            for (int i = 1; i <= counter ; i++) {
              digitalWrite(13, HIGH);
              delay(200);
              digitalWrite(13, LOW);
              delay(200);
            }
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            delay(200);
            digitalWrite(12, LOW);
            return;
          }
          else if (j == 2) {
            counter = 0;
            EEPROM.update(6, counter);
            delay(10);
            digitalWrite(13, HIGH);
            digitalWrite(12, HIGH);
            delay(500);
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            return;
          }
        }
      }
    }
    digitalWrite(12, LOW);
    if (i > 15) {
      temp++;
      i = 0;
      while (digitalRead(rb) == HIGH) {
        delay(1);
        i++;
        if (i > 500) {
          digitalWrite(13, HIGH);
          digitalWrite(12, HIGH);
          delay(200);
          digitalWrite(13, LOW);
          digitalWrite(12, LOW);
          counter = temp;
          EEPROM.update(6, counter);
          delay(10);
          return;
        }
      }
      goto a;
    }
  }
}




int rightswitch() {
  short int i = 0, cl = 0, j;
  if (digitalRead(lb) == LOW) {
a:  while (digitalRead(lb) == LOW) {
      delay(1);
      digitalWrite(13, HIGH);
      i++; 
      int t = 0;
      while (digitalRead(lb) == LOW && digitalRead(rb) == LOW) {
        t++;
        delay(1);
        if (t > 100) {
          digitalWrite(12, HIGH);
          while (digitalRead(lb) == LOW && digitalRead(rb) == LOW);
          (digitalRead(lb) == LOW) ? j = 1 : j = 2;
          (digitalRead(lb) == LOW) ? digitalWrite(13, LOW) : digitalWrite(12, LOW);
          while (digitalRead(lb) == LOW || digitalRead(rb) == LOW);
          (j == 1)? mos(10*spl, 10*spr) : remote_control();
          return;
        }
      }       
    }
    digitalWrite(13, LOW);
    if (i > 15) {
      cl++;
      i = 0;
      while (digitalRead(lb) == HIGH) {
        delay(1);
        i++;
        if (i > 500) {
          return cl;
        }
      }
      goto a;
    }
  }
  return cl;
}
