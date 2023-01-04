void menu(byte a){
  switch(a){
    case 1: clock_update(); break;
    case 2: alarm_update(); break;
    case 3: date_update(); break;
  }
}
