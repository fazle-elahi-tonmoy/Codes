void motor_run (byte i){
  digitalWrite(motor_pins[i], 1);
  delay(motor_delay[i]);
  digitalWrite(motor_pins[i], 0);
}