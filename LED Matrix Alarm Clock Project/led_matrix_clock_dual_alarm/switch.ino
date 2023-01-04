byte menu_press(byte a) {
  int p = 0;
  while (!digitalRead(menu_button)) {
    p++; delay(1);
    if (p > 15) digitalWrite(led, 1);
    if ((p >= 500 && a != 2) || a == 1) {
      digitalWrite(led, 0);
      if (a == 1) delay(100);
      return 1;
    }
  }
  if (p > 15) {
    digitalWrite(led, 0); return 2;
  }
  return 0;
}

byte set_press(byte a) {
  int p = 0;
  while (!digitalRead(set_button)) {
    p++; delay(1);
    if (p > 15) digitalWrite(led, 1);
    if ((p >= 500 && a != 2) || a == 1) {
      digitalWrite(led, 0);
      if (a == 1) delay(100);
      return 1;
    }
  }
  if (p > 15) {
    digitalWrite(led, 0); return 2;
  }
  return 0;
}

byte long_press() {
  int p = 0;
  while (!digitalRead(set_button)) {
    p++; delay(1);
    if (p > 15) digitalWrite(led, 1);
    if (p > long_press_timer * 1000) {
      digitalWrite(led, 0); return 1;
    }
  }
  if (p > 15) {
    digitalWrite(led, 0); return 2;
  }
  return 0;
}

byte tap_press() {
  int count = 0;
d: int p = 0;
  while (!digitalRead(menu_button)) {
    p++; delay(1);
    if (p > 15) digitalWrite(led, 1);
  }
  if (p > 15) {
    digitalWrite(led, 0); count++; p = 0;
    while (digitalRead(menu_button)) {
      p++; delay(1);
      if (p > 500) return count;
    }
    goto d;
  }
  return count;
}

byte special_press() {
  int p = 0;
  while (!digitalRead(special_button)) {
    p++; delay(1);
    if (p > 15) digitalWrite(led, 1);
  }
  if (p > 15) {
    digitalWrite(led, 0); return 1;
  }
  return 0;
}
