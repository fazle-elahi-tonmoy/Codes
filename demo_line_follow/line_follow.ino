void line_follow(){
  while (1) { //infinite loop
    if (sensor == 0b001100) motor(100, 100); //straight line detection, straight go

    //if robot moves out to right from center position
    else if (sensor == 0b001000) motor(90, 100);
    else if (sensor == 0b011000) motor(70, 100);
    else if (sensor == 0b010000) motor(50, 100);
    else if (sensor == 0b110000) motor(30, 100);
    else if (sensor == 0b100000) motor(0, 100);

    //if robot moves out to left from center position
    else if (sensor == 0b000100) motor(100, 90);
    else if (sensor == 0b000110) motor(100, 70);
    else if (sensor == 0b000010) motor(100, 50);
    else if (sensor == 0b000011) motor(100, 30);
    else if (sensor == 0b000001) motor(100, 0);

    //if robot detects sharp 90 degree turn
    else if (sensor == 0b111100 || sensor == 0b111000 || sensor == 0b111110) flag = 'l'; //if it detects left turn, it won't do anything initialy. it will activate when there will be no line before the robot
    else if (sensor == 0b001111 || sensor == 0b001111 || sensor == 0b001111) flag = 'r'; //i can't gurantee if robot will go completely straight. so i added two more logic if robot slightly deviate to left or right

    //if robot don't find any line before it then it will activate flag according to the value previously assigned by sharp turn detection
    else if (sensor == 0b000000) {
      (flag != 's')? digitalWrite(blue_led, HIGH) : digitalWrite(blue_led, LOW); //if robot detects any sharp turn logic beforehand, it will turn on the led
      if (flag == 'l') while (sensor != 0b001100) motor(-100, 100); //if the flag indicates left turn, then it will turn to left untill it completely aligns with the center position.
      else if (flag == 'r') while (sensor != 0b001100) motor(100, -100); //the negative speed indicated in function means the right motor will go backward at 100 pwm speed
      flag = 's'; //once we have done turning, we dont need to use the flag anymore. it will change automatically if robot again detects any turn logic.
      digitalWrite(blue_led, LOW);
    }
  }
}
