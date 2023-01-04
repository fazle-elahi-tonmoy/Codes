char F[3][3] = {{'G', 'G', 'G'}, {'G', 'G', 'G'}, {'G', 'G', 'G'}};
char B[3][3] = {{'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'}};
char U[3][3] = {{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
char D[3][3] = {{'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}};
char L[3][3] = {{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}};
char R[3][3] = {{'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'}};
char T[3];
int i, j;
int count = 0;




void setup() {
  Serial.begin(9600);
  display_cube();
  r_clock();
  f_clock();
  d_clock();
  l_clock();
  u_clock();
  b_clock();
  r_anti_clock();
  f_anti_clock();
  d_anti_clock();
  l_anti_clock();
  u_anti_clock();
  b_anti_clock();
  display_cube();
  cube_solving();  
}
void loop(){

}

void cube_solving() {
  first_step(); //cross matching
  display_cube();
  second_step(); //corner matching
  display_cube();
  third_step();  //edge matching....2nd layer complete
  display_cube();
  fourth_step(); // down side cross matching
  display_cube();
  fifth_step(); //down side full matching
  display_cube();
  sixth_step(); //OLL algorithm
  display_cube();
  seventh_step(); //PLL algorithm and final solving
  display_cube();
  Serial.print(count);
}

