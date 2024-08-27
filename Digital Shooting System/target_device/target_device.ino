#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define button 3
bool debug = 0;
RF24 radio(9, 10);  // CE, CSN
const byte addresses[6] = "radio1";
const byte addresses2[7] = "trigger";
int value = 1234;

const int mux_pin1[4] = { 8, 7, 6, 5 };
const int mux_pin2[4] = { A1, A0, A2, A3 };
int mux1_value[16], mux2_value[16];
int mux_hor_value_range[25] = { 990, 970, 950, 930, 910, 890, 870, 850, 830, 810, 790, 770, 750, 730, 710, 690, 670, 650, 630, 610, 590, 570, 550, 530, 300 };
int mux2_hor_value_range[9][25] = { { 985, 965, 940, 920, 900, 880, 855, 835, 830, 815, 795, 775, 755, 735, 720, 710, 690, 655, 645, 500, 500, 500, 500, 500, 500 },
                                    { 985, 950, 930, 910, 890, 870, 850, 830, 810, 790, 770, 750, 730, 710, 690, 670, 650, 500, 500, 500, 500, 500, 500, 500, 500 },
                                    { 985, 950, 930, 910, 890, 870, 825, 805, 785, 765, 745, 725, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 },
                                    { 985, 965, 945, 910, 890, 870, 850, 825, 805, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 },
                                    { 985, 965, 940, 920, 900, 880, 860, 840, 810, 770, 755, 735, 715, 695, 685, 665, 645, 628, 615, 600, 500, 500, 500, 500, 500 },
                                    { 980, 950, 930, 910, 890, 870, 845, 825, 805, 785, 765, 745, 725, 705, 685, 665, 645, 628, 500, 500, 500, 500, 500, 500, 500 },
                                    { 980, 960, 940, 915, 895, 870, 850, 830, 810, 790, 770, 750, 730, 700, 680, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 },
                                    { 980, 960, 940, 920, 895, 875, 855, 820, 800, 780, 760, 740, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 },
                                    { 980, 960, 930, 910, 890, 870, 850, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 } };
int special_sensor_count[9] = { 19, 18, 14, 10, 21, 19, 16, 13, 8 };
int mux1_ver_value_range[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, -1, -2, -3, -4 };
int mux2_ver_value_range[14] = { -5, -6, -7, -8, -9, 11, 12, 13, 14, -10, -11, -12, -13, -14 };
bool hit = 0;

int posx = 0, posy = 0;

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Radio Failed!");
  }
  radio.openReadingPipe(1, addresses2);
  radio.openWritingPipe(addresses);
  radio.setPALevel(RF24_PA_MIN);
  radio.setPayloadSize(sizeof(value));
  radio.startListening();
  pinMode(button, INPUT);
  for (byte i = 0; i < 4; i++) {
    pinMode(mux_pin1[i], OUTPUT);
    pinMode(mux_pin2[i], OUTPUT);
    digitalWrite(mux_pin2[i], 1);
  }
}

void loop() {

  if (radio.available()) {
    radio.read(&value, sizeof(value));
    radio.stopListening();
    if (value == 1111) {
      hit = 0;
      for (byte i = 0; i < 15; i++) {
        posx = mux1_array_check(i);
        posy = mux1_ver_value_range[i];
        if (hit) {
          Serial.println(String(posx) + "," + String(posy) + " " + "mux1");
          break;
        }
      }

      if (!hit) {
        for (byte i = 0; i < 14; i++) {
          posx = mux2_array_check(i);
          posy = mux2_ver_value_range[i];
          if (hit) {
            Serial.println(String(posx) + "," + String(posy) + " " + "mux2");
            break;
          }
        }
      }


      if (hit) {
        posx += 12;
        posy += 12;
        value = posx * 100 + posy;
        radio.openWritingPipe(addresses);
        bool report = radio.write(&value, sizeof(value));
        (report) ? Serial.println("Message Sent: " + String(value)) : Serial.println("Sending Failed!");
        delay(500);
      }

      else {
        value = 6666;
        radio.openWritingPipe(addresses);
        bool report = radio.write(&value, sizeof(value));
        (report) ? Serial.println("Message Sent: " + String(value)) : Serial.println("Sending Failed!");
        delay(500);
      }
      radio.startListening();
    }
  }

  byte r = push();
  if (r) {
    if (r == 1) {
      debug = 1;
      Serial.println("Debug Mode Activated");
    } else if (r == 2) {
      while (1) {
        for (int i = 0; i < 15; i++) {
          mux1_value[i] = mux1_check(i);
          if (mux1_value[i] > 999)
            ;
          else if (mux1_value[i] > 99) Serial.print("0");
          else if (mux1_value[i] > 9) Serial.print("00");
          else Serial.print("000");
          Serial.print(String(mux1_value[i]) + " ");
        }
        Serial.println();
        delay(250);
      }
    }

    else if (r == 3) {
      while (1) {
        for (int i = 0; i < 14; i++) {
          mux2_value[i] = mux2_check(i);
          if (mux2_value[i] > 999)
            ;
          else if (mux2_value[i] > 99) Serial.print("0");
          else if (mux2_value[i] > 9) Serial.print("00");
          else Serial.print("000");
          Serial.print(String(mux2_value[i]) + " ");
        }
        Serial.println();
        delay(250);
      }
    }
  }

  if (debug) {
    bool flag = 0;
    bool flag_2 = 0;
    for (int i = 0; i < 15; i++) {
      mux1_value[i] = mux1_check(i);
      if (mux1_value[i] > 300) flag = 1;
    }

    for (int i = 0; i < 14; i++) {
      mux2_value[i] = mux2_check(i);
      if (i == 1) mux2_value[i] = 0;
      else if (mux2_value[i] > 300) flag_2 = 1;
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
      delay(550);
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
      delay(550);
    }
  }
}