int spd = 9, position = 0;
bool BTisConnected = 0;
String device_name;
void send_data(byte select) {
  display.setTextSize(2);
  display.setTextColor(1);
  for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
  if (select) {
    SerialBT.begin("joystick remote", true);
    SerialBT.setTimeout(10000);
    SerialBT.register_callback(onBluetoothStateChange);
    device_name = readStringFromEEPROM(select * 11);
recon:
    byte charlen = device_name.length();
    String disp;
    for (int i = 0; i < (10 - charlen) / 2; i++) disp += " ";
    disp += device_name;
    display.clearDisplay();
    display.setTextSize(2);
    text("CONNECTING", 04, 12);
    (charlen % 2) ? text(disp, 11, 36) : text(disp, 4, 36);
    display.display();
    BTisConnected = SerialBT.connect(device_name);
    if (BTisConnected) {
      display.clearDisplay();
      text("CONNECTED!", 04, 24);
      display.display();
    }

    else {
      bool request_check = reconnect_panel(0);
      if (request_check) goto recon;
      else return;
    }
  }
  for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
  display.setTextSize(4);
  display.clearDisplay();
  show_char("S");
  display.display();
  uint32_t connection_timer = millis();
  while (1) {
    if (select) {
      if (!BTisConnected) {
        bool request_check = reconnect_panel(1);
        if (request_check) goto recon;
        else break;
      }
    }
    int p = recheck();
    if (p == 8) {
      display.clearDisplay();
      if (joystick[3] == -1) SerialBT.print(show_char("T"));
      else if (joystick[3] == 1) SerialBT.print(show_char("D"));
      else SerialBT.print(show_char("N"));
      display.display();
    }

    else if (p) {
      display.clearDisplay();
      if (joystick[1] == 1 && joystick[2] == 1) SerialBT.print(show_char("G"));
      else if (joystick[1] == -1 && joystick[2] == 1) SerialBT.print(show_char("H"));
      else if (joystick[1] == 1 && joystick[2] == -1) SerialBT.print(show_char("I"));
      else if (joystick[1] == -1 && joystick[2] == -1) SerialBT.print(show_char("J"));
      else if (joystick[1] == 1) SerialBT.print(show_char("F"));
      else if (joystick[1] == -1) SerialBT.print(show_char("B"));
      else if (joystick[2] == 1) SerialBT.print(show_char("L"));
      else if (joystick[2] == -1) SerialBT.print(show_char("R"));
      else if (!button_val[0] && !button_val[1]) break;
      else if (!button_val[0]) SerialBT.print(show_char("w"));
      else if (!button_val[1]) SerialBT.print(show_char("W"));
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
      (l == 1) ? position++ : position--;
      if (position > 9) position = 9;
      if (position < 0) position = 0;
      char x = 'k' + position;
      SerialBT.print(show_char(String(x)));
      display.display();
    }
  }
  SerialBT.disconnect();
  display.setTextSize(2);
}

String show_char(String s) {
  text(String(position) + " " + s + " " + String(spd), 04, 24);
  return s;
}

bool reconnect_panel(bool a) {
  bool menu = 0;
  for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
  while (1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    text("CONNECTION", 04, 8);
    (a) ? text("  LOST!", 11, 32) : text("  FAILED!", 06, 32);
    display.setTextSize(1);
    text("           RECONNECT", 04, 55);
    text("EXIT", 04, 55);
    display.display();
    if (push(l1)) {
      menu = 0;
      break;
    } else if (push(r1)) {
      menu = 1;
      break;
    }
  }
  display.setTextSize(2);
  return menu;
}

void onBluetoothStateChange(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) BTisConnected = 1;
  else if (event == ESP_SPP_CLOSE_EVT) BTisConnected = 0;
}