bool fire_read() {
  bool flag = 0;
  fire[0] = analogRead(irL);
  fire[1] = analogRead(irF);
  fire[2] = analogRead(irR);
  for (byte i = 0; i < 3; i++)
    if (fire[i] < 4000) flag = 1;
  return flag;
}

void fire_follow() {
  bool following = fire_read();
  if (following) {
    if (fire[0] < fire[1]) x = 'L';
    else if (fire[2] < fire[1]) x = 'R';
    else x = 'F';

    if (fire[1] < threshold && x == 'F') {
      motor(0, 0);
      digitalWrite(pump, 1);
      for (byte j = 0; j < 5; j++) {
        if (j == 4) digitalWrite(pump, 0);
        for (int i = 50; i < 130; i++) {
          nozzle.write(i);
          delay(5);
        }
        for (int i = 130; i > 50; i--) {
          nozzle.write(i);
          delay(5);
        }
      }
      following = 0;
    }

  } else x = 'S';
}