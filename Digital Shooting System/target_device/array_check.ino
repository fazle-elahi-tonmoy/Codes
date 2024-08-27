int mux1_array_check(byte a) {
  mux1_value[a] = mux1_check(a);
  if (mux1_value[a] > 300) {
    for (int i = 0; i < 10; i++)
      if (mux1_value[a] < mux1_check(a)) mux1_value[a] = mux1_check(a);
    hit = 1;
  }
  int score = 12;
  if (hit) {
    for (int i = 0; i < 25; i++) {
      if (mux1_value[a] > mux_hor_value_range[i]) return score;
      score--;
    }
  }
  return 13;
}

int mux2_array_check(byte a) {
  mux2_value[a] = mux2_check(a);
  if (a == 1) mux2_value[a] = 0;
  if (mux2_value[a] > 300) {
    for (int i = 0; i < 10; i++)
      if (mux2_value[a] < mux2_check(a)) mux2_value[a] = mux2_check(a);
    hit = 1;
  }
  int score = 12;
  if (a > 4) score = special_sensor_count[a - 5] / 2;
  if (hit) {
    for (int i = 0; i < 25; i++) {
      if (i < 5) {
        if (mux2_value[a] > mux_hor_value_range[i]) return score;
      } else {
        if (mux2_value[a] > mux2_hor_value_range[a - 5][i]) return score;
      }
      score--;
    }
  }
  return 13;
}