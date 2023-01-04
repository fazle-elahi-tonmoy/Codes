void servo1_speed_update(byte a) {
  switch (a) {
    case 1:
      (servo1_act[0]) ? servo1_speed = servo1_right_rotation_speed : servo1_speed = servo1_left_rotation_speed;
      break;
    case 2:
      (servo1_act[0]) ? servo1_wait = servo1_right_waiting_time : servo1_wait = servo1_left_waiting_time;
      break;
    case 3:
      (servo1_act[0]) ? servo1_speed = servo1_right_to_mid_rotation_speed : servo1_speed = servo1_left_to_mid_rotation_speed;
      break;
    case 4:
      servo1_wait = servo1_mid_waiting_time;
      break;
    case 5:
      (servo1_act[1]) ? servo1_speed = servo1_right_rotation_speed : servo1_speed = servo1_left_rotation_speed;
      break;
    case 6:
      (servo1_act[1]) ? servo1_wait = servo1_right_waiting_time : servo1_wait = servo1_left_waiting_time;
      break;
    case 7:
      (servo1_act[1]) ? servo1_speed = servo1_right_to_mid_rotation_speed : servo1_speed = servo1_left_to_mid_rotation_speed;
      break;
  }
}

void servo2_speed_update(byte a) {
  switch (a) {
    case 1:
      (servo2_act[0]) ? servo2_speed = servo2_right_rotation_speed : servo2_speed = servo2_left_rotation_speed;
      break;
    case 2:
      (servo2_act[0]) ? servo2_wait = servo2_right_waiting_time : servo2_wait = servo2_left_waiting_time;
      break;
    case 3:
      (servo2_act[0]) ? servo2_speed = servo2_right_to_mid_rotation_speed : servo2_speed = servo2_left_to_mid_rotation_speed;
      break;
    case 4:
      servo2_wait = servo2_mid_waiting_time;
      break;
    case 5:
      (servo2_act[1]) ? servo2_speed = servo2_right_rotation_speed : servo2_speed = servo2_left_rotation_speed;
      break;
    case 6:
      (servo2_act[1]) ? servo2_wait = servo2_right_waiting_time : servo2_wait = servo2_left_waiting_time;
      break;
    case 7:
      (servo2_act[1]) ? servo2_speed = servo2_right_to_mid_rotation_speed : servo2_speed = servo2_left_to_mid_rotation_speed;
      break;
  }
}
