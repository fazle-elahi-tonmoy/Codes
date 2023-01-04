void leftlog() {
  left();
  while (1) {
    sensor();
    if (v3 == 0 && v4 == 0) break;
  }
  st_left();
  while (1) {
    sensor();
    if (v3 == 1 && v4 == 1) break;
  }
}

void rightlog() {
  right();
  while (1) {
    sensor();
    if (v3 == 0 && v4 == 0) break;
  }
  st_right();
  while (1) {
    sensor();
    if (v3 == 1 && v4 == 1) break;
  }
}

void leftlog2() {
  st_left();
  while (1) {
    sensor();
    if (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1) break;
    if (v3 == 0 && v4 == 0) break;
  }
  st_left();

  while (1) {
    sensor();
    if (v3 == 1 && v4 == 1) break;
  }
}

void rightlog2() {
  left();
  while (1) {
    sensor();
    if (v1 == 1 && v2 == 1 && v3 == 1 && v4 == 1 && v5 == 1 && v6 == 1) break;
    if (v3 == 0 && v4 == 0) break;
  }
  st_right();
  while (1) {
    sensor();
    if (v3 == 1 && v4 == 1) break;
  }
}
void cavelog() {
  sonar();
  sensor();
  if (sf < 30 && sf != 0) {
    stp();
    if(a==1||a==2) sonfleft();
    else sonfright();
    
  }
  else if (sr < maxdis && sr != 0) {
    if (sf < 30 && sf != 0 && (a==1||a==2)) sonfleft();
    else if (sf < 30 && sf != 0 && a==0) sonfright();
    else if ((sr < middis) && a==0 && sr!=0) sonleft();
    else if ((sr > middis) && a==0 && sr!=0) sonright();
    else if ((sl < middis) && (a==1||a==2) && sl!=0) sonright();
    else if ((sl > middis) && (a==1||a==2) && sl!=0) sonleft();    
    else sonstraight();
  }
}

