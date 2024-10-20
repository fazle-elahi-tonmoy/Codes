void debugging_sys() {
  if (debug) {
    bool flag = 0;
    bool flag_2 = 0;
    for (int i = 0; i < 15; i++) {
      mux1_value[i] = mux1_check(i);
      if (mux1_value[i] > 500) flag = 1;
    }

    for (int i = 0; i < 14; i++) {
      mux2_value[i] = mux2_check(i);
      if (mux2_value[i] > 500) flag_2 = 1;
    }
    
    if (flag) {
      for (int i = 0; i < 15; i++) {
        if (mux1_value[i] > 999)
          ;
        else if (mux1_value[i] > 99) Serial.print("0");
        else if (mux1_value[i] > 9) Serial.print("00");
        else Serial.print("000");
        Serial.print(String(mux1_value[i]) + " ");
      }
      Serial.println("mux1");
      digitalWrite(buzzer, 1);
      delay(250);
      digitalWrite(buzzer, 0);
      delay(300);
      reminder = millis();
    }

    else if (flag_2) {
      for (int i = 0; i < 14; i++) {
        if (mux2_value[i] > 999)
          ;
        else if (mux2_value[i] > 99) Serial.print("0");
        else if (mux2_value[i] > 9) Serial.print("00");
        else Serial.print("000");
        Serial.print(String(mux2_value[i]) + " ");
      }
      Serial.println("mux2");
      digitalWrite(buzzer, 1);
      delay(250);
      digitalWrite(buzzer, 0);
      delay(300);
      reminder = millis();
    }
  }
}