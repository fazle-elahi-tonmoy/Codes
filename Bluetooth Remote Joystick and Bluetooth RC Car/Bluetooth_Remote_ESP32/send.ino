int spd = 9, pos = 0;
void send_data() {
  SerialBT.begin("joystick remote", true);
  int select = 0, temp = 255;
  while (!push(calb)) {
    if (temp != select) {
      temp = select;
      display.clearDisplay();
      text("  BRC " + String(select), 04, 8);
      display.display();
    }
    byte l = Lencoder_read();
    byte r = Rencoder_read();
    if (r == 1 || l == 1) select++;
    else if (r == 2 || l == 2) select--;
    if (select > 99) select = 99;
    if (select < 0) select = 0;
  }
  if (select) {
    String device_name = "BRC " + String(select);
    display.clearDisplay();
    text("CONNECTING", 04, 8);
    display.display();
    bool connected = SerialBT.connect(device_name);
    if (connected) {
      display.clearDisplay();
      text("CONNECTED!", 04, 8);
      display.display();
    }

    else {
      display.clearDisplay();
      text(" FAILED! ", 11, 8);
      display.display();
      delay(1000);
      return;
    }
  }

  display.setTextSize(4);

  while (!press(calb)) {
    int p = recheck();
    if (p == 4) {
      display.clearDisplay();
      if (joystick[2] == 1) SerialBT.print(show_char("T"));
      else if (joystick[2] == -1) SerialBT.print(show_char("D"));
      else SerialBT.print(show_char("N"));
      display.display();
    }

    else if (p) {
      display.clearDisplay();
      if (joystick[0] == -1 && joystick[3] == -1) SerialBT.print(show_char("G"));
      else if (joystick[0] == 1 && joystick[3] == -1) SerialBT.print(show_char("H"));
      else if (joystick[0] == -1 && joystick[3] == 1) SerialBT.print(show_char("I"));
      else if (joystick[0] == 1 && joystick[3] == 1) SerialBT.print(show_char("J"));
      else if (joystick[0] == -1) SerialBT.print(show_char("F"));
      else if (joystick[0] == 1) SerialBT.print(show_char("B"));
      else if (joystick[3] == -1) SerialBT.print(show_char("L"));
      else if (joystick[3] == 1) SerialBT.print(show_char("R"));
      else if (!button_val[6]) SerialBT.print(show_char("w"));
      else if (!button_val[7]) SerialBT.print(show_char("W"));
      else if (!button_val[2]) SerialBT.print(show_char("g"));
      else if (!button_val[3]) SerialBT.print(show_char("h"));
      else if (!button_val[4]) SerialBT.print(show_char("i"));
      else if (!button_val[5]) SerialBT.print(show_char("j"));
      else SerialBT.print(show_char("S"));
      display.display();
    }

    byte r = Rencoder_read();
    if (r) {
      display.clearDisplay();
      (r == 1) ? spd++ : spd--;
      if (spd > 9) spd = 9;
      if (spd < 0) spd = 0;
      char x = '0' + spd;
      SerialBT.print(show_char(String(x)));
      display.display();
    }

    byte l = Lencoder_read();
    if (l) {
      display.clearDisplay();
      (l == 1) ? pos++ : pos--;
      if (pos > 9) pos = 9;
      if (pos < 0) pos = 0;
      char x = 'k' + pos;
      SerialBT.print(show_char(String(x)));
      display.display();
    }
  }
  display.setTextSize(2);
}

String show_char(String s) {
  text(String(pos) + " " + s + " " + String(spd), 04, 02);
  return s;
}