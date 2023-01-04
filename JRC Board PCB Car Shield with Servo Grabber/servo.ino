void servo_initiate() {
  handl.attach(13, 500, 2500);
  handr.attach(05, 500, 2500);
  lift.attach(23, 500, 2500);
  handl.write(dropl);
  handr.write(dropr);
  lift.write(rise);
}