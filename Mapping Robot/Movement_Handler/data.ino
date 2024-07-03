void data_entry() {
  if (millis() - k_timer > 500) {
    k_timer = millis();
    value_print(x);
    value_print(y);
    incoming();
    if (!inc) {
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ARROW);
      delay(10);
      bleKeyboard.releaseAll();
    }
    inc = 0;
  }

  if (millis() - w_timer > 2000 && !scan) {
    w_timer = millis();
    Serial1.write('S');
    scan = 1;
  }
}

void value_print(int x) {
  char c;
  if (x < 0) bleKeyboard.write('-');
  int p = abs(x);
  for (int i = digit_length(p) - 1; i >= 0; i--) {
    c = '0' + extract_digit(p, i);
    bleKeyboard.write(c);
  }
  bleKeyboard.write(KEY_RIGHT_ARROW);
}

int digit_length(int number) {
  int count = 0;
  do {
    number /= 10;
    count++;
  } while (number != 0);
  return count;
}

int extract_digit(int number, int decimal_place) {
  while (decimal_place > 0) {
    number /= 10;
    decimal_place--;
  }
  return number % 10;
}