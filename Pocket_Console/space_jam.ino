void space_jam() {
  u8g2.begin();
  while (1) {
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.setFontDirection(0);
    u8g2.setFontRefHeightAll();

    st_Setup(u8g2.getU8g2());

    for (;;) {

      st_Step(y, /* is_auto_fire */ 0, /* is_fire */ !digitalRead(SW));
      u8g2.firstPage();

      do {
        st_Draw(0);
      } while (u8g2.nextPage());

      if (!digitalRead(down)) {
        y++;
      }

      if (!digitalRead(up)) {
        y--;
      }
    }
  }
}