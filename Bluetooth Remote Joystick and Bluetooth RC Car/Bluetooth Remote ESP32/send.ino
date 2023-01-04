void send_data() {
  starting_sequence();
  SerialBT.begin("joystick remote", true);
  bool connected = SerialBT.connect("BRC");
  digitalWrite(5, connected);

  while (!press(calb)) {
    int p = recheck();
    if (p == 8) {
      if (pot_val[2] == 1) SerialBT.print("T");
      else if (pot_val[2] == -1) SerialBT.print("D");
      else SerialBT.print("N");
    }

    else if (p > 2) {
      if (pot_val[0] == -1 && pot_val[3] == -1) SerialBT.print("G");
      else if (pot_val[0] == 1 && pot_val[3] == -1) SerialBT.print("H");
      else if (pot_val[0] == -1 && pot_val[3] == 1) SerialBT.print("I");
      else if (pot_val[0] == 1 && pot_val[3] == 1) SerialBT.print("J");
      else if (pot_val[0] == -1) SerialBT.print("F");
      else if (pot_val[0] == 1) SerialBT.print("B");
      else if (pot_val[3] == -1) SerialBT.print("L");
      else if (pot_val[3] == 1) SerialBT.print("R");
      else if (!button_val[0]) SerialBT.print("w");
      else if (!button_val[1]) SerialBT.print("W");
      else if (!button_val[2]) SerialBT.print("g");
      else if (!button_val[3]) SerialBT.print("h");
      else if (!button_val[4]) SerialBT.print("i");
      else if (!button_val[5]) SerialBT.print("j");
      else SerialBT.print("S");
    }

    else if (p == 2) {
      SerialBT.print(pot_val[4]);
      Serial.print(pot_val[4]);
    }
    else if (p == 1) {
      char c = pot_val[5] + 'k';
      SerialBT.print(c);
      Serial.print(c);
    }
  }
}