byte menu() {
  display.clearDisplay();
  short int cl = 255, b = 0, list = 5, temp = 0;
  while (1) {
    if (cl != temp) {
      cl = temp;
      display_icon(b, cl);
    }
    byte l = Lencoder_read();
    byte r = Rencoder_read();
    if (r == 1 || l == 1) {
      temp++;
      if (temp > list) {
        temp = 0;
        b = 0;
      } else if (temp > b + 3) b++;
    }

    else if (r == 2 || l == 2) {
      temp--;
      if (temp < 0) {
        temp = list;
        b = list - 3;
      } else if (temp < b) b--;
    }

    byte p = push(0);
    if(p){
      if(p == 1) return cl + 1;
      else return 0;
    }
  }
}