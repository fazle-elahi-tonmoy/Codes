
void left() {
  analogWrite(lmf, 0);
  analogWrite(lmb, 0);
  analogWrite(rmf, spdt);
  analogWrite(rmb, 0);
}
void hleft() {
  analogWrite(lmf, 60);
  analogWrite(lmb, 0);
  analogWrite(rmf, spds);
  analogWrite(rmb, 0);
}
void hright() {
  analogWrite(lmf, 60);
  analogWrite(lmb, 0);
  analogWrite(rmf, spds);
  analogWrite(rmb, 0);
}
void rleft() {
  analogWrite(lmf, 0);
  analogWrite(lmb, spds);
  analogWrite(rmf, 0);
  analogWrite(rmb, 0);
}
void rright() {
  analogWrite(lmf, 0);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, spds);
}
void right() {
  analogWrite(lmf, spdt);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, 0);
}
void straight() {
  analogWrite(lmf, spds);
  analogWrite(lmb, 0);
  analogWrite(rmf, spds);
  analogWrite(rmb, 0);
}
void l_straight() {
  analogWrite(lmf, 70);
  analogWrite(lmb, 0);
  analogWrite(rmf, 70);
  analogWrite(rmb, 0);
}
void st_left() {
  analogWrite(lmf, 0);
  analogWrite(lmb, spdt);
  analogWrite(rmf, spdt);
  analogWrite(rmb, 0);
}
void st_right() {
  analogWrite(lmf, spdt);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, spdt);
}
void l_left() {
  analogWrite(lmf, spdl);
  analogWrite(lmb, 0);
  analogWrite(rmf, spds);
  analogWrite(rmb, 0);
}
void l_right() {
  analogWrite(lmf, spds);
  analogWrite(lmb, 0);
  analogWrite(rmf, spdl);
  analogWrite(rmb, 0);
}
void stp() {
  analogWrite(lmf, 0);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, 0);
}
void back() {
  analogWrite(lmf, 0);
  analogWrite(lmb, spds);
  analogWrite(rmf, 0);
  analogWrite(rmb, spds);
}

void sonleft() {
  analogWrite(lmf, 60);
  analogWrite(lmb, 0);
  analogWrite(rmf, 100);
  analogWrite(rmb, 0);
}
void sonright() {
  analogWrite(lmf, 100);
  analogWrite(lmb, 0);
  analogWrite(rmf, 60);
  analogWrite(rmb, 0);
}
void sonfright() {
  analogWrite(lmf, 150);
  analogWrite(lmb, 0);
  analogWrite(rmf, 0);
  analogWrite(rmb, 0);
}
void sonfleft() {
  analogWrite(rmf, 150);
  analogWrite(lmb, 0);
  analogWrite(lmf, 0);
  analogWrite(rmb, 0);
}
void sonstraight() {
  analogWrite(lmf, 120);
  analogWrite(lmb, 0);
  analogWrite(rmf, 120);
  analogWrite(rmb, 0);
}

